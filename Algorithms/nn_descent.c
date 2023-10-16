#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "dataset.h"
#include "reverse.h"
#include "nng_initialization.h"
#include "nn_descent.h"

/*Heap * nn_descent(Dataset dataset, int k, Metric metric) {

    int c, r_neighbour, r_r_neighbour, n_r_neighbour;

    Heap *heap = nng_initialization_random(dataset, k, metric);
    Stack *R;
    int **B = malloc(dataset->numberOfObjects * sizeof(int *));
   
    do {
        R = reverse(heap, dataset->numberOfObjects);
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            B[i] = heap_getIndexes(heap[i]);
        }
        c = 0;
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            while (!stack_empty(R[i])) {

                //Neighbour of reverse neighbour
                r_neighbour = stack_pop(R[i]);
                for (int j = 0; j < k; j++) {
                    if (B[r_neighbour][j] == i) continue;
                    //printf("1 %f\n", metric(dataset->objects[i]->features, dataset->objects[B[r_neighbour][j]]->features, dataset->dimensions));
                    c += heap_update(heap[i], B[r_neighbour][j], metric(dataset->objects[i]->features, dataset->objects[B[r_neighbour][j]]->features, dataset->dimensions));
                }
                
                //Reverse neighbour of reverse neighbour
                while (!stack_empty(R[r_neighbour])) {
                    r_r_neighbour = stack_pop(R[r_neighbour]);
                    if (r_r_neighbour == i) continue;
                    //printf("2 %f\n", metric(dataset->objects[i]->features, dataset->objects[r_r_neighbour]->features, dataset->dimensions));
                    c += heap_update(heap[i], r_r_neighbour, metric(dataset->objects[i]->features, dataset->objects[r_r_neighbour]->features, dataset->dimensions));
                }
                
            }

            for (int l = 0; l < k; l++) {

                //reverse neighbour of neighbour
                while (!stack_empty(R[B[i][l]])) {
                    n_r_neighbour = stack_pop(R[B[i][l]]);
                    if (n_r_neighbour == i) continue;
                    //printf("3 %f\n", metric(dataset->objects[i]->features, dataset->objects[n_r_neighbour]->features, dataset->dimensions));
                    c += heap_update(heap[i], n_r_neighbour, metric(dataset->objects[i]->features, dataset->objects[n_r_neighbour]->features, dataset->dimensions));
                }
                
                //Neighbour of neighbour
                for (int z = 0; z < k; z++) {
                    if (B[B[i][l]][z] == i) continue;
                    //printf("4 %f\n", metric(dataset->objects[i]->features, dataset->objects[B[B[i][l]][z]]->features, dataset->dimensions));
                    c += heap_update(heap[i], B[B[i][l]][z], metric(dataset->objects[i]->features, dataset->objects[B[B[i][l]][z]]->features, dataset->dimensions));
                }
            } 
        }

        for (int i = 0; i < dataset->numberOfObjects; i++) {
            stack_free(R[i]);
            free(B[i]);
        }
        free(R);

        printf("%d\n", c);

   } while (c);
   
   free(B);
   return heap;
}*/



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
            free(B);
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
        //printf("%d\n", c);
    } while(c);
    
    return heap;
}