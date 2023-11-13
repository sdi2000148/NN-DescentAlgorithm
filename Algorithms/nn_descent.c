#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

int **nn_descent(Dataset dataset, int k, Metric metric) {
    double val, rate;
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), c, index, index1, index2, temp, evaluations = 0, **neighbours, flag,
    sampling = (int)(0.4 *(float)k), count;
    Heap *heaps = nng_initialization_random(dataset, k, metric); // nng initialization of random graph
    List *old = malloc(objects * sizeof(List)), *new = malloc(objects * sizeof(List)), *old_r = malloc(objects * sizeof(List)), *new_r = malloc(objects * sizeof(List));
    Listnode neighbour1, neighbour2;
    float d = 0.001;


    do {
        c = 0;

        for(int i = 0; i < objects; i++) {
            list_initialize(&old[i]);
            list_initialize(&new[i]);
            count = 0;
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    list_insert(old[i], index);
                }
                else if(count <= sampling) { // sampling
                    list_insert(new[i], index);
                    heap_setFlag(heaps[i], j);
                    count++;
                }
            }
        }

        // reverse calcuation

        //reverse(old, old_r, objects);
        //reverse(new, new_r, objects);
        strict_reverse(old, old_r, objects, heaps);
        strict_reverse(new, new_r, objects, heaps);

        for(int i = 0; i < objects; i++) {
            list_union(old[i], old_r[i], sampling);
            list_union(new[i], new_r[i], sampling);

            neighbour1 = list_head(new[i]);
            while(neighbour1 != NULL) {
                index1 = listnode_data(neighbour1);

                neighbour2 = list_next(neighbour1);
                while(neighbour2 != NULL) {
                    index2 = listnode_data(neighbour2);
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    evaluations++;
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    neighbour2 = list_next(neighbour2);
                }
                neighbour2 = list_head(old[i]);
                while(neighbour2 != NULL) {
                    index2 = listnode_data(neighbour2);
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    evaluations++;
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    neighbour2 = list_next(neighbour2);
                }

                neighbour1 = list_next(neighbour1);
            }
        }

        for(int i = 0; i < objects; i++) {
            list_free(old[i]);
            list_free(new[i]);
        }

        printf("%d\n", c);
    } while(c > (int)(d * (float)(objects * k)));

    temp = objects * (objects-1);
    rate = (double)(evaluations) / ((double)temp / (double)2); // scan rate
    printf("nn descent better scan-rate: %f\n", rate);

    neighbours = getNeighbours(heaps, objects, k);

    heap_free_all(heaps, objects);
    free(old);
    free(new);
    free(old_r);
    free(new_r);

    return neighbours;
}

