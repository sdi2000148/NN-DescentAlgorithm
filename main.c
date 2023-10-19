#include <stdio.h>
#include <stdlib.h>
#include "metrics.h"
#include "brutal.h"
#include "recall.h"
#include "heap.h"
#include "list.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#include <time.h>


int main(void) {
    int D = 2, N = 10000, k = 20, *array, count = 0; 
    clock_t start_time, end_time;

    Dataset dataset;

    array = malloc(N*D*sizeof(int));

    srand(1);

    for(int i = 0; i < N*D; i++) {
        array[i] = rand()%1000+1;
    }

    dataset_initialize(&dataset, N, D);


    for(int i = 0; i < N; i++) {
        for(int j = 0; j < D; j++) {
            dataset_addFeature(dataset, i, j, &array[count]);
            count++;
        }
    }



    start_time = clock();
    Heap *actual = brute_force(dataset, k, l2);   // brute force
    end_time = clock();
    printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    
    //Heap *predicted_2 =  nng_initialization_random(dataset, k, l2);                   // nn descent

    //if (predicted_1 == NULL){
    //   exit(EXIT_FAILURE);
    //}

    //lists = reverse(actual, N);

    /*for(int i = 0; i < N; i++) {
        printf("reverse neighbours of object %d:  ", i);
        listnode = list_head(lists[i]);

        while(listnode != NULL) {
            printf("%d ", listnode_data(listnode));
            listnode = list_next(listnode);
        }
        printf("\n");
    }*/

    //dataset_print(dataset);
   /* printf("\n") ;
    for (int i=0 ; i<dataset->numberOfObjects ; i++){
        printf("object %d: ", i) ; 
        heap_print(predicted_1[i]);
    }*/

    /*for (int i=0 ; i<N ; i++){
        printf("object %d: ", i) ; 
        //heap_print(actual[i]);
        //heap_print(predicted_1[i]);
        //printf("\n");
    }*/


    double rec = recall(actual, predicted_1, N, k);
    printf("recall nn_descent: %f\n",rec*100) ;

    /*rec = recall(actual, predicted_2, N, k);
    printf("recall nn_initialization: %f\n",rec*100) ;*/

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

    free(array);

    return 0;
}