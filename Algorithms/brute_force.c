#include <stdio.h>
#include "brutal.h"
#include "heap.h"


int brute_force(Dataset dataset, int k, Metric metric)
{
    for (int i=0 ; i < dataset->numberOfObjects ; i++){       
        heap_initialize(&dataset->objects[i]->heap, k);
        for (int j=0 ; j < dataset->numberOfObjects ; j++){
            if (j == i) continue;
            heap_update(dataset->objects[i]->heap, j, metric(dataset->objects[i]->features, dataset->objects[j]->features, dataset->dimensions));
        }
    }
    return 0;
}
