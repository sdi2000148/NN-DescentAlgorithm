#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "PriorityQueue.h"
#include <time.h>


Dataset dataset_create(int dimensions, int numberOfObjects) {
    Object object;
    Dataset dataset = malloc(sizeof(*dataset));

    dataset->objects = malloc(numberOfObjects*sizeof(Object));
    dataset->dimensions = dimensions;
    dataset->numberOfObjects = numberOfObjects;

    srand(5);

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

void nng_initialization(Dataset dataset, int k, Metric metric) {
    int index, *samples, unique;
    samples = malloc(dataset->numberOfObjects*sizeof(int));

    for (int i = 0; i < dataset->numberOfObjects; i++) {
        Initialize(&dataset->objects[i]->priorityQueue, k);

        for(int j = 0; j < dataset->numberOfObjects; j++) {
            samples[j] = 0;
        }

        samples[i] = 1;
        for(int j = 0; j < k; j++) {
            unique = 0;
            do {
                index = rand() % dataset->numberOfObjects;
                if(samples[index] == 0) {
                    unique = 1;
                    samples[index] = 1;
                }
            } while(!unique);

            Insert(dataset->objects[i]->priorityQueue, index, metric(dataset->objects[index]->features, dataset->objects[i]->features, dataset->dimensions));
        }
    }

    free(samples);
}



void dataset_print(Dataset dataset) {
    for (int i=0 ; i < dataset->numberOfObjects ; i++){
        Print_PQ(dataset->objects[i]->priorityQueue); 
    }
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
        Free(dataset->objects[i]->priorityQueue);
        free(dataset->objects[i]->features);
        free(dataset->objects[i]);
    }
    free(dataset->objects);
    free(dataset);
}