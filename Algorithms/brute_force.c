#include <stdio.h>
#include "brutal.h"
#include "heap.h"
#include <stdlib.h>

//κανω ολους τους ελεγχους για να βρω την πραγματικη λυση 
Heap* brute_force(Dataset dataset, int k, Metric metric) {

    int objects = dataset_getNumberOfObjects(dataset), replaced, evaluations;
    Heap *heaps = malloc(objects * (sizeof(Heap)));
    
    for (int i=0 ; i < objects ; i++){       
        heap_initialize(&heaps[i], k);
        for (int j=0 ; j < objects ; j++){
            if (j == i) continue;
            evaluations++;
            heap_update(heaps[i], j, metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, j), dataset_getDimensions(dataset)), &replaced);
        }
    }

    return heaps; 
}
