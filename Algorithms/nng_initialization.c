#include <stdio.h>
#include <stdlib.h>
#include "nng_initialization.h"
#include "services.h"
#include "avl.h"
#include "time.h"
#include "metrics.h"

Heap* nng_initialization_random(Dataset dataset, int k, Metric metric) {
    int objects = dataset_getNumberOfObjects(dataset), index, *samples, unique;
    Heap *heaps = malloc(objects* (sizeof(Heap)));
    float val;

    srand(time(NULL));

    samples = malloc(objects*sizeof(int));

    if (objects <= k) {
        printf("K is bigger or equal than the given objects!\n");
        return NULL;
    }

    // initialize ADTs
    for (int i = 0; i < objects; i++) {
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


            val = metric(dataset, index, i);
            heap_update(heaps[i], index, val);
        }
    }

    free(samples);
    return heaps;
}



