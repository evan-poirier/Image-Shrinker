#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

// open the file, create an ImagePPM, and return the pointer
// return NULL if the file cannot be opened

ImagePPM *readPPM(char *filename)
{
    // open the file
    FILE* fptr;
    fptr = fopen(filename, "r");

    // return null if file could not be opened correctly
    if (!fptr) return NULL;

    // create ImagePPM struct to later be returned
    ImagePPM* newPPM = malloc(sizeof(ImagePPM));

    // assign variables of ImagePPM struct
    // assign magic identifier
    fscanf(fptr, "%s", newPPM->magic);

    //assign numRows and numcols
    fscanf(fptr, "%d", &newPPM->numCols);
    fscanf(fptr, "%d", &newPPM->numRows);

    //assign maximum color value
    fscanf(fptr, "%d", &newPPM->maxVal);

    // malloc pixel array
    newPPM->pixels = malloc(sizeof(Pixel*) * newPPM->numRows);
    for (int r = 0; r < newPPM->numRows; r ++) {
        newPPM->pixels[r] = malloc(sizeof(Pixel) * newPPM->numCols);
    }

    // read pixel values
    for (int r = 0; r < newPPM->numRows; r ++) {
        for (int c = 0; c < newPPM->numCols; c ++) {
            fscanf(fptr, "%d", &newPPM->pixels[r][c].red);
            fscanf(fptr, "%d", &newPPM->pixels[r][c].green);
            fscanf(fptr, "%d", &newPPM->pixels[r][c].blue);
        }
    }    

    // close file
    fclose(fptr);

    return newPPM;
}

// open the file and write the ImagePPM to the file
// return 1 on success
// return 0 if the file cannot be opened

int writePPM(ImagePPM *pImagePPM, char *filename)
{
    // open the file
    FILE* fptr;
    fptr = fopen(filename, "w");

    // return null if file could not be opened correctly
    if (!fptr) return 0;

    // print ImagePGM data into file
    fprintf(fptr, "%s\n", pImagePPM->magic); // magic identifier
    fprintf(fptr, "%d %d\n", pImagePPM->numCols, pImagePPM->numRows); // columns and rows
    fprintf(fptr, "%d\n", pImagePPM->maxVal); // maximum intensity

    for (int r = 0; r < pImagePPM->numRows; r ++) {
        for (int c = 0; c < pImagePPM->numCols; c ++) {
            fprintf(fptr, "%d %d %d\t", pImagePPM->pixels[r][c].red, pImagePPM->pixels[r][c].green, pImagePPM->pixels[r][c].blue);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);

    return 1;
}

// free the ImagePPM and its pixels
// everything with a malloc needs a free

void freePPM(ImagePPM *pImagePPM)
{
    for (int r = 0; r < pImagePPM->numRows; r ++) {
        free(pImagePPM->pixels[r]);
    }
    free(pImagePPM->pixels);
    free(pImagePPM);

    return;
}

// open the file, create an ImagePGM, and return the pointer
// return NULL if the file cannot be opened

ImagePGM *readPGM(char *filename)
{
    // open the file
    FILE* fptr;
    fptr = fopen(filename, "r");

    // return null if file could not be opened correctly
    if (!fptr) return NULL;

    // create ImagePGM struct to later be returned
    ImagePGM* newPGM = malloc(sizeof(ImagePGM));

    // assign variables of ImagePGM struct
    // assign magic identifier
    fscanf(fptr, "%s", newPGM->magic);

    //assign numRows and numcols
    fscanf(fptr, "%d", &newPGM->numCols);
    fscanf(fptr, "%d", &newPGM->numRows);

    //assign maximum color value
    fscanf(fptr, "%d", &newPGM->maxVal);

    // malloc pixel array
    newPGM->pixels = malloc(sizeof(int*) * newPGM->numRows);
    for (int r = 0; r < newPGM->numRows; r ++) {
        newPGM->pixels[r] = malloc(sizeof(int) * newPGM->numCols);
    }

    // read pixel values
    for (int r = 0; r < newPGM->numRows; r ++) {
        for (int c = 0; c < newPGM->numCols; c ++) {
            fscanf(fptr, "%d", &newPGM->pixels[r][c]);
        }
    }    

    // close file
    fclose(fptr);

    return newPGM;
}

// open the file and write the ImagePGM to the file
// return 1 on success
// return 0 if the file cannot be opened

int writePGM(ImagePGM *pImagePGM, char *filename)
{
    // open the file
    FILE* fptr;
    fptr = fopen(filename, "w");

    // return null if file could not be opened correctly
    if (!fptr) return 0;

    // print ImagePGM data into file
    fprintf(fptr, "%s\n", pImagePGM->magic); // magic identifier
    fprintf(fptr, "%d %d\n", pImagePGM->numCols, pImagePGM->numRows); // columns and rows
    fprintf(fptr, "%d\n", pImagePGM->maxVal); // maximum intensity

    for (int r = 0; r < pImagePGM->numRows; r ++) {
        for (int c = 0; c < pImagePGM->numCols; c ++) {
            fprintf(fptr, "%d ", pImagePGM->pixels[r][c]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);

    return 1;
}

// free the ImagePGM and its pixels
// everything with a malloc needs a free

void freePGM(ImagePGM *pImagePGM)
{
    for (int r = 0; r < pImagePGM->numRows; r ++) {
        free(pImagePGM->pixels[r]);
    }
    free(pImagePGM->pixels);
    free(pImagePGM);

    return;
}

ImagePGM *convertToPGM(ImagePPM *pImagePPM)
{
    // create ImagePGM struct to later be returned
    ImagePGM* newPGM = malloc(sizeof(ImagePGM));

    // assign variables of ImagePGM struct
    // assign magic identifier
    strcpy(newPGM->magic, "P2");

    //assign numRows and numcols
    newPGM->numCols = pImagePPM->numCols;
    newPGM->numRows = pImagePPM->numRows;

    //assign maximum color value
    newPGM->maxVal = pImagePPM->maxVal;

    // malloc pixel array
    newPGM->pixels = malloc(sizeof(int*) * newPGM->numRows);
    for (int r = 0; r < newPGM->numRows; r ++) {
        newPGM->pixels[r] = malloc(sizeof(int) * newPGM->numCols);
    }

    // assign each pixel value with the average of the corresponding RGB values from pImagePPM
    for (int r = 0; r < newPGM->numRows; r ++) {
        for (int c = 0; c < newPGM->numCols; c ++) {
            int sum = pImagePPM->pixels[r][c].red + pImagePPM->pixels[r][c].green + pImagePPM->pixels[r][c].blue;
            newPGM->pixels[r][c] = sum / 3;
        }
    }

    return newPGM;
}

ImagePGM *shrinkPGM(ImagePGM *pImagePGM)
{
    // create ImagePGM struct to later be returned
    ImagePGM* newPGM = malloc(sizeof(ImagePGM));

    // assign variables of ImagePGM struct
    // assign magic identifier
    strcpy(newPGM->magic, "P2");

    //assign numRows and numcols
    newPGM->numCols = pImagePGM->numCols / 2;
    newPGM->numRows = pImagePGM->numRows / 2;

    //assign maximum color value
    newPGM->maxVal = pImagePGM->maxVal;

    // malloc pixel array
    newPGM->pixels = malloc(sizeof(int*) * newPGM->numRows);
    for (int r = 0; r < newPGM->numRows; r ++) {
        newPGM->pixels[r] = malloc(sizeof(int) * newPGM->numCols);
    }

    // find the average of each 2x2 box
    for (int r = 0; r < pImagePGM->numRows / 2; r ++) {
        for (int c = 0; c < pImagePGM->numCols / 2; c ++) {
            int sum = 0;
            sum += pImagePGM->pixels[r * 2][c * 2]; //top left
            sum += pImagePGM->pixels[r * 2][(c * 2) + 1]; //top right
            sum += pImagePGM->pixels[(r * 2) + 1][(c * 2)]; //bottom left
            sum += pImagePGM->pixels[(r * 2) + 1][(c * 2) + 1]; //bottom right

            newPGM->pixels[r][c] = sum / 4;
        }
    }

    return newPGM;
}