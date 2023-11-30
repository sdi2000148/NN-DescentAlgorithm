#include <stdio.h>
#include <stdlib.h>
#include "brute_force.h"
#include "heap.h"
#include "services.h"


int **brute_force(Dataset dataset, int k, Metric metric) {
    double val;
    int objects = dataset_getNumberOfObjects(dataset), **neighbours;
    Heap *heaps = malloc(objects * (sizeof(Heap)));
    
    for (int i=0 ; i < objects ; i++){       
        heap_initialize(&heaps[i], k);
        for (int j=0 ; j < objects ; j++){
            if (j == i) continue;
            val = metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, j), dataset_getDimensions(dataset));
            heap_update(heaps[i], j, val);
        }
    }

    neighbours = getNeighbours(heaps, objects, k);

    heap_free_all(heaps, objects);

    return neighbours; 
}
