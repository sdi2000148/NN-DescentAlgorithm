#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#define TREES 2
#define THRESHOLD k + 1

static float get_random(void) { return ((float)rand() / (float)RAND_MAX); }

int **nn_descent(Dataset dataset, Metric metric, int k, double p, double d) 
{
    int    objects = dataset_getNumberOfObjects(dataset), c, index, index1, index2, **neighbours, flag;
    int    sampling = (int)(p *(double)k), count1, count2;
    int    threshold = (int)(d * (double)(objects * k));
    float  val;
    Heap   *heaps, *new = malloc(objects * sizeof(Heap)), *old = malloc(objects * sizeof(Heap));

    // Initializing knn graph with random neighbors
    heaps = nng_initialization_random(dataset, k, metric);
    if(heaps == NULL){
        return NULL;
    }

    // Initializing heaps for each object
    for(int i = 0; i < objects; i++) {
        heap_initialize(&old[i], k + sampling);
        heap_initialize(&new[i], 2*sampling);
    }

    // Start of nn-descent
    do {
        c = 0;
        
        // reverse, union and sample in one full pass (fast single core paper)
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
        
        // Local join for every object 
        for(int i = 0; i < objects; i++){
            // No need to conduct local join if no new objects are present
            if(heap_empty(new[i]) == 0) {

                // Conduct local join between new objects and old objects
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

                // Local join between the last new object and the old objects.
                // This is done to empty the old heap, so as to be used in the next iteration:
                // no need for free and malloc.
                index1 = heap_getIndex(new[i], count1);
                while((index2 = heap_remove(old[i])) != -1) {
                    val = metric(dataset, index1, index2);
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                }

                // Conduct local join between new ojects.
                // remove is used to empty the new heap, in order to avoid unnecessary frees and mallocs later
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

    } while(c > threshold);

    // Get graph as 2D array
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


/* Parallelized implementation, but linear single core traversal still exists (probably bad idea) */
int **nn_descent_parallel(Dataset dataset, Metric metric, int k, double p, double d) {
    int objects = dataset_getNumberOfObjects(dataset), c, index, index1, index2, **neighbours, flag,
    sampling = (int)(p *(double)k), count1, count2;
    Heap *heaps, *new = malloc(objects * sizeof(Heap)), *old = malloc(objects * sizeof(Heap));
    float val;

    if(metric == l2) {
        heaps = nng_initialization_rpt(dataset, metric, k, TREES, THRESHOLD);
    }
    else {
        heaps = nng_initialization_random(dataset, k, metric);
    }

    if(heaps == NULL) {
        return NULL;
    }

    
    // parallel for
    for(int i = 0; i < objects; i++) {
        heap_initialize(&old[i], k + sampling);
        heap_initialize(&new[i], 2*sampling);
    }

    do {
        c = 0;

        // parallel for
        for(int i = 0; i < objects; i++) {
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    heap_update(old[i], index, -1.0);
                }
                else { 
                    heap_update(new[i], index, get_random());
                    heap_setFlag(heaps[i], j);
                }
            }
        }
        
        // single
        for(int i = 0; i < objects; i++) {
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    heap_update(old[index], i, get_random());
                }
                else {
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


