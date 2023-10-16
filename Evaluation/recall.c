#include <stdio.h>
#include <stdlib.h>
#include "recall.h"

double recall(Heap *actual, Heap *predicted, int N, int k)
{
    int true_positive = 0 ;
    int *pred, *act ;

    for (int i=0 ; i<N ; i++){
        act = heap_getIndexes(actual[i]);
        pred = heap_getIndexes(predicted[i]);
        for (int l=0 ; l<k ; l++){
            for (int j=0 ; j<k; j++){
                if (act[l] == pred[j]){
                    true_positive++;
                    break;
                }
            }
        }
        free(pred);
        free(act);
    }
    //printf("%d\n", true_positive) ;
    return (double) (true_positive) / (double) (N * k) ;  
}