#include <stdio.h>
#include <stdlib.h>
#include "metrics.h"
#include "brutal.h"
#include "recall.h"
#include "heap.h"
#include "list.h"
#include "reverse.h"
#include "nng_initialization.h"
#include "nn_descent.h"


int main(void) {
    int D = 2, N = 5, k = 2; 
    //Stack *stack;

    Dataset dataset = dataset_create(D, N);

    Heap *actual = brute_force(dataset, k, l2);   // brute force
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    //Heap *predicted_2 =  nng_initialization_random(dataset, k, l2);                   // nn descent

    if (predicted_1 == NULL){
       exit(EXIT_FAILURE);
    }


    /*for(int i = 0; i < N; i++) {
        printf("reverse of object %d:  ", i);
        while(!stack_empty(stack[i])) {
            printf("%d  " , stack_pop(stack[i]));
        }
        printf("\n");
    }*/

    //dataset_print(dataset);
   /* printf("\n") ;
    for (int i=0 ; i<dataset->numberOfObjects ; i++){
        printf("object %d: ", i) ; 
        heap_print(predicted_1[i]);
    }*/

  //  for (int i=0 ; i<N ; i++){
      //  heap_print(actual[i]);
       // heap_print(predicted_1[i]);
       // printf("\n");
   // }


    double rec = recall(actual, predicted_1, N, k);
    printf("recall: %f\n",rec*100) ;

    /*for (int i=0 ; i<N ; i++){
        int *actual_indexes = heap_getIndexes(actual[i]);
        for (int j=0 ; j<k ; j++){
            printf("%d  ",actual_indexes[j]);
        }
        printf("\n"); 
        free(actual_indexes) ;
    }*/

    dataset_free(dataset);
    heap_free_all(actual, N);
    heap_free_all(predicted_1, N);

    //for(int i = 0; i < N; i++) {
   //     stack_free(stack[i]);
   // }
   // free(stack);

    return 0;
}