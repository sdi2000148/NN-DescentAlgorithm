#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "brutal.h"

double l2(int *x, int *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = abs(x[i]- y[i]);
        result += pow(value, 2.0);
    }
    return sqrt(result);
}


double recall(Heap *actual, Heap *predicted, int N, int k)
{
    int true_positive = 0 ;
    int *pred, *act ;

    for (int i=0 ; i<N ; i++){
        pred = heap_getIndexes(predicted[i]);
        act = heap_getIndexes(actual[i]);
        for (int i=0 ; i<k ; i++){
            for (int j=0 ; j<k; j++){
                if (act[i] == pred[j]){
                    true_positive++;
                    continue;
                }
            }
        }
        free(pred);
        free(act);
    }
    //printf("%d\n", true_positive) ;
    return (double) (true_positive) / (double) (N * k) ;  
}



int main(void) {
    int D = 2, N = 5, k = 2; 

    Dataset dataset = dataset_create(D, N);


    Heap *actual = brute_force(dataset, k, l2);   // brute force
    Heap *predicted_1 =  nng_initialization(dataset, k, l2);                   // nn descent

    if (predicted_1 == NULL){
        exit(EXIT_FAILURE);
    }

    dataset_print(dataset);
    printf("\n") ;
    /*for (int i=0 ; i<dataset->numberOfObjects ; i++){
        heap_print(actual[i]);
    }*/

    for (int i=0 ; i<N ; i++){
        heap_print(actual[i]);
        heap_print(predicted_1[i]);
        printf("\n");
    }


    double rec = recall(actual, predicted_1, N, k);
    printf("recall: %f\n",rec*100) ;

    dataset_free(dataset);
    heap_free_all(actual, N);
    heap_free_all(predicted_1, N);

    

    return 0;
}