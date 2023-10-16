#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "dataset.h"
#include "reverse.h"
#include "nng_initialization.h"
#include "nn_descent.h"

Heap * nn_descent(Dataset dataset, int k, Metric metric) {
    List *R;
    int *B, c, index;
    Listnode neighbour, n_neighbour;
    
    Heap *heap = nng_initialization_random(dataset, k, metric);

    do {
        R = reverse(heap, dataset->numberOfObjects);
        //printf("reverse end\n");
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            B = heap_getIndexes(heap[i]);
            for (int j = 0; j < k; j++){
                list_insert(R[i], B[j]); 
            }
            //free(B);
        }

        c = 0;

        for(int i = 0; i < dataset->numberOfObjects; i++) {
            neighbour = list_head(R[i]);
            while(neighbour != NULL) {
                n_neighbour = list_head(R[listnode_data(neighbour)]);
                while(n_neighbour != NULL) {
                    index = listnode_data(n_neighbour);
                    //rintf("%d\n", index);
                    if(index == i) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    c += heap_update(heap[i], index, metric(dataset->objects[i]->features, dataset->objects[index]->features, dataset->dimensions));
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            list_free(R[i]);
        }
        free(R);
        printf("%d\n", c);
    } while(c);
    
    return heap;
}