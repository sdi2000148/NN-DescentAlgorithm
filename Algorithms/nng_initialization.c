#include <stdio.h>
#include <stdlib.h>
#include "nng_initialization.h"
#include "services.h"
#include "avl.h"

Heap* nng_initialization_random(Dataset dataset, int k, Metric metric) {
    int index, *samples, unique, replaced;
    Heap *heaps = malloc(dataset_getNumberOfObjects(dataset) * (sizeof(Heap)));
    samples = malloc(dataset_getNumberOfObjects(dataset)*sizeof(int));

    // srand() ... 

    if (dataset_getNumberOfObjects(dataset) < k) {
        printf("K is bigger than the given objects!\n");
        return NULL;
    }

    for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
        heap_initialize(&heaps[i], k);
    }
    
    
    for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {

        for(int j = 0; j < dataset_getNumberOfObjects(dataset); j++) {
            samples[j] = 0;
        }

        samples[i] = 1;
        for(int j = 0; j < k; j++) {
            unique = 0;
            do {
                index = rand() % dataset_getNumberOfObjects(dataset);
                if(samples[index] == 0) {
                    unique = 1;
                    samples[index] = 1;
                }
            } while(!unique);

            heap_update(heaps[i], index, metric(dataset_getFeatures(dataset, index), dataset_getFeatures(dataset, i), dataset_getDimensions(dataset)), &replaced);
        }
    }

    free(samples);

    return heaps;
}



