#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

Heap * nn_descent(Dataset dataset, int k, Metric metric) {
    List *R = malloc(dataset_getNumberOfObjects(dataset) * sizeof(List));
    List *U = malloc(dataset_getNumberOfObjects(dataset) * sizeof(List));
    int *B, c, index;
    Listnode neighbour, n_neighbour, temp;
    
    Heap *heap = nng_initialization_random(dataset, k, metric, R);

    do {
        /*R = reverse(heap, dataset->numberOfObjects);
        //printf("reverse end\n");
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            B = heap_getIndexes(heap[i]);
            for (int j = 0; j < k; j++){
                list_insert(R[i], B[j]); 
            }
            //free(B);
        }*/

        for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
            list_initialize(&U[i]);
            B = heap_getIndexes(heap[i]);
            for (int j = 0; j < k; j++){
                list_insert(U[i], B[j]); 
            }
            temp = list_head(R[i]);
            while (temp != NULL) {
                list_insert(U[i], listnode_data(temp));
                temp = list_next(temp);
            }
            
        }

        c = 0;

        for(int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
            neighbour = list_head(U[i]);
            while(neighbour != NULL) {
                n_neighbour = list_head(U[listnode_data(neighbour)]);
                while(n_neighbour != NULL) {
                    index = listnode_data(n_neighbour);
                    //rintf("%d\n", index);
                    if(index == i) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    c += nn_update(heap, i, index, metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, index), dataset_getDimensions(dataset)), R);
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }
        for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
            list_free(U[i]);
        }
 
        printf("%d\n", c);
    } while(c);

    for (int i = 0; i < dataset_getNumberOfObjects(dataset); i++) {
        list_free(R[i]);
    }
    free(R);
    free(U);
    
    return heap;
}