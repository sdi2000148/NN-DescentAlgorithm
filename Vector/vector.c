#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"


float *hyperplane_vector_init(Dataset dataset, int index1, int index2) {
    int dimensions = dataset_getDimensions(dataset), objects = dataset_getNumberOfObjects(dataset);
    float *features1 = dataset_getFeatures(dataset, index1), *features2 = dataset_getFeatures(dataset, index2), *vector = malloc(dimensions * sizeof(float));

    if(index1 >= objects || index2 >= objects) {
        return NULL;
    }

    for(int i = 0; i < dimensions; i++) {
        vector[i] = features1[i] - features2[i];
    }

    return vector;
}

float *hyperplane_midpoint_init(Dataset dataset, int index1, int index2) {
    int dimensions = dataset_getDimensions(dataset), objects = dataset_getNumberOfObjects(dataset);
    float *features1 = dataset_getFeatures(dataset, index1), *features2 = dataset_getFeatures(dataset, index2), *midpoint = malloc(dimensions * sizeof(float));

    if(index1 >= objects || index2 >= objects) {
        return NULL;
    }

    for(int i = 0; i < dimensions; i++) {
        midpoint[i] = (features1[i] + features2[i]) / 2;
    }

    return midpoint;
}


float inner_product(float *vector1, float *vector2, int dimensions, float accumulator) {
    float product = 0.0;
    for(int i = 0; i < dimensions; i++) {
        product += vector1[i] * vector2[i];
    }

    return product + accumulator;

}