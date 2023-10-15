#include <stdio.h>
#include <stdlib.h>
#include "nng_initialization.h"

Heap* nng_initialization_random(Dataset dataset, int k, Metric metric) {
    int index, *samples, unique;
    Heap *heaps = malloc(dataset->numberOfObjects * (sizeof(Heap)));
    samples = malloc(dataset->numberOfObjects*sizeof(int));

    // srand() ... 

    if (dataset->numberOfObjects < k) {
        printf("K is bigger than the given objects!\n");
        return NULL;
    }
    
    for (int i = 0; i < dataset->numberOfObjects; i++) {
        heap_initialize(&heaps[i], k);

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

            heap_update(heaps[i], index, metric(dataset->objects[index]->features, dataset->objects[i]->features, dataset->dimensions));
        }
    }

    free(samples);

    return heaps;
}



