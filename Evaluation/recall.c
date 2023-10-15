#include <stdio.h>
#include <stdlib.h>
#include "recall.h"

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