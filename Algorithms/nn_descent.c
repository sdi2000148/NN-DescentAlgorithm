#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

Heap * nn_descent(Dataset dataset, int k, Metric metric) {
    int objects = dataset_getNumberOfObjects(dataset), replaced, c, index, evaluations = 0;
    List *U;
    Listnode neighbour, n_neighbour;
    Heap *heap = nng_initialization_random(dataset, k, metric);

    do {
        U = reverse(heap, objects);
        c = 0;

        for (int i=0; i < objects; i++) {
            for (int j=0; j < k; j++){
                list_insert(U[i], heap_getIndex(heap[i], j)); 
            }
        }

        for(int i = 0; i < objects; i++) {
            neighbour = list_head(U[i]);
            while(neighbour != NULL) {
                n_neighbour = list_head(U[listnode_data(neighbour)]);
                while(n_neighbour != NULL) {
                    index = listnode_data(n_neighbour);
                    if(index == i) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    evaluations++;
                    c += heap_update(heap[i], index, metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, index), dataset_getDimensions(dataset)), &replaced);
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }

        for (int i = 0; i < objects; i++) {
            list_free(U[i]);
        }
        free(U);

        printf("%d\n", c);
    } while(c);

    int temp = objects * (objects-1);
    double rate = (double)(evaluations) / ((double)temp / (double)2);
    printf("nn descent scan-rate: %f\n", rate);
    
    return heap;
}


Heap * nn_descentBetter(Dataset dataset, int k, Metric metric) {
    int objects = dataset_getNumberOfObjects(dataset), c, index1, index2, evaluations = 0, replaced;
    double met;
    List *U;
    Listnode neighbour, n_neighbour;
    Heap *heap = nng_initialization_random(dataset, k, metric);
    Avl *avls = malloc(objects * sizeof(Avl));

    for(int i = 0; i < objects; i++) {
        avl_initialize(&avls[i]);
    }

    do {
        U = reverse(heap, objects);
        c = 0;
        
        for (int i=0; i < objects; i++) {
            for (int j=0; j < k; j++){
                list_insert(U[i], heap_getIndex(heap[i], j)); 
            }
        }

        for(int i = 0; i < objects; i++) {
            neighbour = list_head(U[i]);
            while(neighbour != NULL) {
                index1 = listnode_data(neighbour);
                n_neighbour = list_next(neighbour);
                while(n_neighbour != NULL) {
                    index2 = listnode_data(n_neighbour);
                   if(avl_search(avls[index1], index2) == 1) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    met = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dataset_getDimensions(dataset));
                    evaluations++;

                    c += heap_update(heap[index1], index2, met, &replaced);
                    c += heap_update(heap[index2], index1, met, &replaced);

                    avl_insert(avls[index1], index2);
                    avl_insert(avls[index2], index1);
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }

        for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
            list_free(U[i]);
        }
        free(U);
 
        printf("%d\n", c);
    } while(c);

    for(int i = 0; i < objects; i++) {
        avl_free(avls[i]);
    }
    free(avls);

    int temp = objects * (objects-1);
    double rate = (double)(evaluations) / ((double)temp / (double)2);
    printf("nn descent better scan-rate: %f\n", rate);
    
    return heap;
}

