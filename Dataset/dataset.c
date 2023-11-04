#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"

struct object {
    Pointer *array;
};


struct dataset {
    int dimensions;
    int numberOfObjects;
    Object *objects;
};

void dataset_initialize(Dataset *dataset, int numberOfObjects, int dimensions) {
    (*dataset) = malloc(sizeof(struct dataset));
    (*dataset)->numberOfObjects = numberOfObjects;
    (*dataset)->dimensions = dimensions;
    (*dataset)->objects = malloc(numberOfObjects*sizeof(Object));

    for(int i = 0; i < numberOfObjects; i++) {
        (*dataset)->objects[i] = malloc(sizeof(struct object));
        (*dataset)->objects[i]->array = calloc(dimensions, sizeof(Pointer)); // initiaize features 
    }
}

int dataset_addFeature(Dataset dataset, int i, int dimension, Pointer feature) {
    if(i > dataset->numberOfObjects || dimension > dataset->dimensions) {
        return -1;
    }
    
    dataset->objects[i]->array[dimension] = feature; // add feature

    return 0;
} 

int dataset_getNumberOfObjects(Dataset dataset) {
    return dataset->numberOfObjects;
}

int dataset_getDimensions(Dataset dataset) {
    return dataset->dimensions;
}

Pointer dataset_getFeature(Dataset dataset, int i, int dimension) {
    if(i > dataset->numberOfObjects || dimension > dataset->dimensions) {
        return NULL;
    }
    return dataset->objects[i]->array[dimension]; // typical indexing
} 

Pointer *dataset_getFeatures(Dataset dataset, int i) {
    if(i > dataset->numberOfObjects) {
        return NULL;
    }

    return dataset->objects[i]->array; // return the whole array 

}


void dataset_free(Dataset dataset) {
    for(int i = 0; i < dataset->numberOfObjects; i++) {
        free(dataset->objects[i]->array);
        free(dataset->objects[i]);
    }
    free(dataset->objects);
    free(dataset);
}