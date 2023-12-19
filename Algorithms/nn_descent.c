#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

static float get_random(void) { return ((float)rand() / (float)RAND_MAX); }

int **nn_descent(Dataset dataset, Metric metric, int k, double p, double d) {
    int objects = dataset_getNumberOfObjects(dataset), c, index, index1, index2, **neighbours, flag,
    sampling = (int)(p *(double)k), count1, count2;
    Heap *heaps, *new = malloc(objects * sizeof(Heap)), *old = malloc(objects * sizeof(Heap));
    float val;

    heaps = nng_initialization_random(dataset, k, metric);
    if(heaps == NULL) {
        return NULL;
    }

    for(int i = 0; i < objects; i++) {
        heap_initialize(&old[i], k + sampling);
        heap_initialize(&new[i], 2*sampling);
    }

    do {
        c = 0;


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
            if(heap_empty(new[i]) == 0) {
                count1 = 0;
                while (count1 < heap_getCount(new[i]) - 1){
                    index1 = heap_getIndex(new[i], count1);
                    count2 = 0;
                    while ((index2 = heap_getIndex(old[i], count2)) != -1){
                        val = metric(dataset, index1, index2);
                        c += heap_update(heaps[index1], index2, val);
                        c += heap_update(heaps[index2], index1, val);
                        count2++;
                    }
                    count1++;
                }

                index1 = heap_getIndex(new[i], count1);
                while((index2 = heap_remove(old[i])) != -1) {
                    val = metric(dataset, index1, index2);
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                }


                while ((index1 = heap_remove(new[i])) != -1){
                    count2 = 0;
                    while ((index2 = heap_getIndex(new[i], count2)) != -1){
                            val = metric(dataset, index1, index2);
                            c += heap_update(heaps[index1], index2, val);
                            c += heap_update(heaps[index2], index1, val);
                            count2++;
                    }
                }
            }

        }

    } while(c > (int)(d * (double)(objects * k)));

    neighbours = getNeighbours(heaps, objects, k);

    for(int i = 0; i < objects; i++) {
        heap_free(new[i]);
        heap_free(old[i]);
    }

    heap_free_all(heaps, objects);
    free(new);
    free(old);

    return neighbours;
}


