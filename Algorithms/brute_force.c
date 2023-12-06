#include <stdio.h>
#include <stdlib.h>
#include "brute_force.h"
#include "heap.h"
#include "services.h"


int **brute_force(Dataset dataset, int k, Metric metric) {
    float val;
    int objects = dataset_getNumberOfObjects(dataset), **neighbours;
    Heap *heaps = malloc(objects * (sizeof(Heap)));


    for(int i = 0; i < objects; i++) {
        heap_initialize(&heaps[i], k);
    }
    
    for (int i=0 ; i < objects ; i++){           
        for (int j=i + 1 ; j < objects ; j++){
            val = metric(dataset, i, j);
            heap_update(heaps[i], j, val);
            heap_update(heaps[j], i, val);
        }
    }

    neighbours = getNeighbours(heaps, objects, k);

    heap_free_all(heaps, objects);

    return neighbours; 
}
