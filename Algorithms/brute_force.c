#include <stdio.h>
#include "brutal.h"
#include "heap.h"
#include <stdlib.h>


Heap* brute_force(Dataset dataset, int k, Metric metric)
{
    int replaced ; // placeholder
    Heap *heaps = malloc(dataset_getNumberOfObjects(dataset) * (sizeof(Heap)));
    for (int i=0 ; i < dataset_getNumberOfObjects(dataset) ; i++){       
        heap_initialize(&heaps[i], k);
        for (int j=0 ; j < dataset_getNumberOfObjects(dataset) ; j++){
            if (j == i) continue;
            heap_update(heaps[i], j, metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, j), dataset_getDimensions(dataset)), &replaced);
        }
    }
    return heaps; 
}
