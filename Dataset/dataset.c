#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "heap.h"
#include <time.h>


Dataset dataset_create(int dimensions, int numberOfObjects) {
    Object object;
    Dataset dataset = malloc(sizeof(*dataset));

    dataset->objects = malloc(numberOfObjects*sizeof(Object));
    dataset->dimensions = dimensions;
    dataset->numberOfObjects = numberOfObjects;

    srand(1);

    for(int i = 0; i < numberOfObjects; i++) {
        object = malloc(sizeof(*object));

        object->features = malloc(dimensions*sizeof(int));

        for(int j = 0; j < dimensions; j++) {
            object->features[j] = rand()%1000+1;
        }
        dataset->objects[i] = object;
    }

    return dataset;
}


void dataset_print(Dataset dataset) {
    for (int i=0 ; i < dataset->numberOfObjects ; i++){
        printf("%d: [ ", i);
        for(int j = 0; j < dataset->dimensions; j++) {
            printf("%d ", dataset->objects[i]->features[j]); 
        }
        printf("]\n");
    }
}


void dataset_free(Dataset dataset) {
    for(int i = 0; i < dataset->numberOfObjects; i++) {
        free(dataset->objects[i]->features);
        free(dataset->objects[i]);
    }
    free(dataset->objects);
    free(dataset);
}