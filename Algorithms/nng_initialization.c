#include <stdio.h>
#include <stdlib.h>
#include "nng_initialization.h"
#include "services.h"
#include "avl.h"

//random αρχικοποιηση της λύσης (γραφου) 
Heap* nng_initialization_random(Dataset dataset, int k, Metric metric, Avl *R) {
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), index, *samples, unique;
    Heap *heaps = malloc(objects* (sizeof(Heap)));

    samples = malloc(objects*sizeof(int));

    if (objects < k) {
        printf("K is bigger than the given objects!\n");
        return NULL;
    }

    for (int i = 0; i < objects; i++) {
        avl_initialize(&R[i]);
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
            } while(!unique);

            nn_update(heaps, i, index, metric(dataset_getFeatures(dataset, index), dataset_getFeatures(dataset, i), dimensions), R);
        }
    }

    free(samples);
    return heaps;
}



