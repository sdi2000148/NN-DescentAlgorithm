#include <stdio.h>
#include <stdlib.h>
#include "nng_initialization.h"
#include "services.h"
#include "avl.h"

Heap* nng_initialization_random(Dataset dataset, int k, Metric metric, Avl *R, Avl *avls) {
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), index, *samples, unique;
    Heap *heaps = malloc(objects* (sizeof(Heap)));
    double val;

    samples = malloc(objects*sizeof(int));

    if (objects < k) {
        printf("K is bigger than the given objects!\n");
        return NULL;
    }

    // initialize ADTs
    for (int i = 0; i < objects; i++) {
        avl_initialize(&R[i]);
        avl_initialize(&avls[i]);
        heap_initialize(&heaps[i], k);
    }
    
    for (int i = 0; i < objects; i++) {
        for(int j = 0; j < objects; j++) 
            samples[j] = 0;

        samples[i] = 1;
        for(int j = 0; j < k; j++) {
            unique = 0;
            do {
                index = rand() % objects;
                if(samples[index] == 0) {
                    unique = 1;
                    samples[index] = 1;
                }
            } while(!unique); // duplicate avoidance 

            if (avl_insert(avls[i], index) == 1) {
                val = metric(dataset_getFeatures(dataset, index), dataset_getFeatures(dataset, i), dimensions);
                nn_update(heaps, i, index, val, R);
            }
        }
    }

    free(samples);
    return heaps;
}



