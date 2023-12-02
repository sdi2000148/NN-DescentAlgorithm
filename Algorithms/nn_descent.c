#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

static double get_random(void) { return ((double)rand() / (double)RAND_MAX); }

int **nn_descent(Dataset dataset, Metric metric, int k, double p, double d) {
    double val;
    long double rate;
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), c, index, index1, index2, **neighbours, flag,
    sampling = (int)(p *(double)k), count1, count2;
    Heap *heaps = nng_initialization_random(dataset, k, metric), *new = malloc(objects * sizeof(Heap)), *old = malloc(objects * sizeof(Heap));

    do {
        c = 0;

        for(int i = 0; i < objects; i++) {
            heap_initialize(&old[i], k + sampling);
            heap_initialize(&new[i], 2*sampling);
        }

        for(int i = 0; i < objects; i++) {
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    heap_update(old[i], index, -1.0);
                    heap_update(old[index], i, get_random());
                }
                else { 
                    heap_update(new[i], index, get_random());
                    heap_setFlag(heaps[i], j);
                    heap_update(new[index], i, get_random());
                }
            }
        }
        

        for(int i = 0; i < objects; i++){
            count1 = 0;
            while ((index1 = heap_getIndex(new[i], count1)) != -1){
                count2 = count1 + 1;
                while ((index2 = heap_getIndex(new[i], count2)) != -1){
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    count2++;
                }
                count2 = 0;
                while ((index2 = heap_getIndex(old[i], count2)) != -1){
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    count2++;
                }
                count1++;
            }
        }

        for(int i = 0; i < objects; i++) {
            heap_free(new[i]);
            heap_free(old[i]);
        }

    } while(c > (int)(d * (double)(objects * k)));

    

    neighbours = getNeighbours(heaps, objects, k);

    heap_free_all(heaps, objects);
    free(new);
    free(old);

    return neighbours;
}


