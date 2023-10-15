#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "dataset.h"
#include "reverse.h"
#include "nng_initialization.h"
#include "nn_descent.h"

Heap * nn_descent(Dataset dataset, int k, Metric metric) {

    int c, r_neighbour, *r_n_neighbour, r_r_neighbour, *n_neighbour, n_r_neighbour, *n_n_neighbour;

   Heap *heap = nng_initialization_random(dataset, k, metric);
   Stack *R;
   
    do {
        R = reverse(heap, dataset->numberOfObjects);
        c = 0;
        for (int i = 0; i < dataset->numberOfObjects; i++) {
            while (!stack_empty(R[i])) {

                //Neighbour of reverse neighbour
                r_neighbour = stack_pop(R[i]);
                r_n_neighbour = heap_getIndexes(heap[r_neighbour]);
                for (int j = 0; j < k; j++) {
                    c += heap_update(heap[i], r_n_neighbour[j], metric(dataset->objects[i]->features, dataset->objects[r_n_neighbour[j]]->features, dataset->dimensions));
                }
                free(r_n_neighbour);
                
                //Reverse neighbour of reverse neighbour
                while (!stack_empty(R[r_neighbour])) {
                    r_r_neighbour = stack_pop(R[r_neighbour]);
                    c += heap_update(heap[i], r_r_neighbour, metric(dataset->objects[i]->features, dataset->objects[r_r_neighbour]->features, dataset->dimensions));
                }
                
            }

            n_neighbour = heap_getIndexes(heap[i]);
            for (int l = 0; l < k; l++) {

                //reverse neighbour of neighbour
                while (!stack_empty(R[n_neighbour[l]])) {
                    n_r_neighbour = stack_pop(R[n_neighbour[l]]);
                    c += heap_update(heap[i], n_r_neighbour, metric(dataset->objects[i]->features, dataset->objects[n_r_neighbour]->features, dataset->dimensions));
                }
                
                //Neighbour of neighbour
                n_n_neighbour = heap_getIndexes(heap[l]);
                for (int z = 0; z < k; z++) {
                    c += heap_update(heap[i], n_n_neighbour[z], metric(dataset->objects[i]->features, dataset->objects[n_n_neighbour[z]]->features, dataset->dimensions));
                }
                free(n_n_neighbour);
            } 
        }

        for (int i = 0; i < dataset->numberOfObjects; i++) {
            stack_free(R[i]);
        }
        free(R);
        
   } while (c);
   
   return heap;
}