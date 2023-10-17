#include <stdio.h>
#include "brutal.h"
#include "heap.h"
#include <stdlib.h>


Heap* brute_force(Dataset dataset, int k, Metric metric)
{
    int replaced ; // placeholder
    Heap *heaps = malloc(dataset->numberOfObjects * (sizeof(Heap)));
    for (int i=0 ; i < dataset->numberOfObjects ; i++){       
        heap_initialize(&heaps[i], k);
        for (int j=0 ; j < dataset->numberOfObjects ; j++){
            if (j == i) continue;
            heap_update(heaps[i], j, metric(dataset->objects[i]->features, dataset->objects[j]->features, dataset->dimensions), &replaced);
        }
    }
    return heaps; 
}
