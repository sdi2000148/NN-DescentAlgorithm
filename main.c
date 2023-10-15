#include <stdio.h>
#include <stdlib.h>
#include "metrics.h"
#include "brutal.h"
#include "recall.h"
#include "heap.h"
#include "nng_initialization.h"


int main(void) {
    int D = 2, N = 5000, k = 2; 

    Dataset dataset = dataset_create(D, N);


    Heap *actual = brute_force(dataset, k, l2);   // brute force
    Heap *predicted_1 =  nng_initialization_random(dataset, k, l2);                   // nn descent

    if (predicted_1 == NULL){
        exit(EXIT_FAILURE);
    }

    //dataset_print(dataset);
    printf("\n") ;
    /*for (int i=0 ; i<dataset->numberOfObjects ; i++){
        heap_print(actual[i]);
    }*/

  //  for (int i=0 ; i<N ; i++){
      //  heap_print(actual[i]);
       // heap_print(predicted_1[i]);
       // printf("\n");
   // }


    double rec = recall(actual, predicted_1, N, k);
    printf("recall: %f\n",rec*100) ;

    dataset_free(dataset);
    heap_free_all(actual, N);
    heap_free_all(predicted_1, N);

    

    return 0;
}