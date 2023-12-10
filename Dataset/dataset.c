#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#define DIMENSIONS 100

struct dataset {
    int dimensions;
    int numberOfObjects;
    float **objects;
    float *squares;
};

void dataset_initialize_sigmod(Dataset *dataset, char *path) {
    int fp;
    uint32_t N;

    fp = open(path, O_RDONLY, 0);

    (*dataset) = malloc(sizeof(struct dataset));

    if(fp == -1) {
        printf("Can't open file\n");
        close(fp);
        return;
    }

    if (read(fp, &N, sizeof(uint32_t)) == 0) {
        printf("Can't read N (number of obects)\n");
        close(fp);
        return;
    }


    (*dataset)->objects = malloc(N * sizeof(float *));
    (*dataset)->numberOfObjects = N;
    (*dataset)->dimensions = DIMENSIONS;
    (*dataset)->squares = malloc(N * sizeof(float));

    for(int i = 0; i < (*dataset)->numberOfObjects; i++) {
        (*dataset)->objects[i] = malloc((*dataset)->dimensions * sizeof(float));
        for(int j = 0; j < (*dataset)->dimensions; j++) {
            if (read(fp, &(*dataset)->objects[i][j], sizeof(float)) == 0) {
                printf("Can't read float (item of obect)\n");
                close(fp);
                return;
            }
        }
    }
}

void dataset_initialize(Dataset *dataset, int N, int dimensions) {
    (*dataset) = malloc(sizeof(struct dataset));
    (*dataset)->objects = malloc(N * sizeof(float *));
    (*dataset)->numberOfObjects = N;
    (*dataset)->dimensions = dimensions;
    (*dataset)->squares = malloc(N * sizeof(float));
    for(int i = 0; i < (*dataset)->numberOfObjects; i++) {
        (*dataset)->objects[i] = calloc((*dataset)->dimensions, sizeof(float));
    }


}


int dataset_addFeature(Dataset dataset, int i, int dimension, float feature) {
    if(i > dataset->numberOfObjects || dimension > dataset->dimensions) {
        return -1;
    }
    
    dataset->objects[i][dimension] = feature; // add feature

    return 0;
} 

int dataset_getNumberOfObjects(Dataset dataset) {
    return dataset->numberOfObjects;
}

int dataset_getDimensions(Dataset dataset) {
    return dataset->dimensions;
}

float dataset_getFeature(Dataset dataset, int i, int dimension) {
    if(i > dataset->numberOfObjects || dimension > dataset->dimensions) {
        return -1.0;
    }
    return dataset->objects[i][dimension]; // typical indexing
}

float *dataset_getFeatures(Dataset dataset, int i) {
    if(i > dataset->numberOfObjects) {
        return NULL;
    }
    return dataset->objects[i]; // typical indexing
}

void dataset_calculateSquares(Dataset dataset) {
    float result;

    for(int i = 0; i < dataset->numberOfObjects; i++) {
        result = 0.0;
        for(int j = 0; j < dataset->dimensions; j++) {
            result += dataset->objects[i][j]*dataset->objects[i][j];
        }   
        dataset->squares[i] = result;
    }
}

float dataset_getSquare(Dataset dataset, int i) {
    if(i > dataset->numberOfObjects) {
        return -1.0;
    }
    return dataset->squares[i];
}


void dataset_free(Dataset dataset) {
    for(int i = 0; i < dataset->numberOfObjects; i++) {
        free(dataset->objects[i]);
    }
    free(dataset->objects);
    free(dataset->squares);
    free(dataset);
}