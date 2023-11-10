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
    sampling = (int)(0.5 *(float)k), count;
    Avl *new = malloc(objects * sizeof(Avl)), *old = malloc(objects * sizeof(Avl)); // incremental search avls
    Heap *heaps = nng_initialization_random(dataset, k, metric); // nng initialization of random graph
    List *old_u = malloc(objects * sizeof(List)), *new_u = malloc(objects * sizeof(List));
    Listnode neighbour1, neighbour2;
    float d = 0.001;


    do {
        c = 0;

        for(int i = 0; i < objects; i++) {
            avl_initialize(&old[i]);
            avl_initialize(&new[i]);
            count = 0;
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    avl_insert(old[i], index);
                }
                else if(count <= sampling) { // sampling
                    avl_insert(new[i], index);
                    heap_setFlag(heaps[i], j);
                    count++;
                }
            }
        }

        // reverse calcuation

        reverse(old, old_u, objects);
        reverse(new, new_u, objects);

        for(int i = 0; i < objects; i++) {
            avl_copyToList(old[i], old_u[i], sampling);
            avl_copyToList(new[i], new_u[i], sampling);

            neighbour1 = list_head(new_u[i]);
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
                neighbour2 = list_head(old_u[i]);
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
            avl_free(old[i]);
            avl_free(new[i]);
            list_free(old_u[i]);
            list_free(new_u[i]);
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
    free(old_u);
    free(new_u);

    return neighbours;
}

