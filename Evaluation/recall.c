#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recall.h"

#define BUFFER_SIZE 1024

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
        //free(pred);
        //free(act);
    }
    //printf("%d\n", true_positive) ;
    return (double) (true_positive) / (double) (N * k) ;  
}


double recall_new(char *filename, Heap *predicted, int N, int k, Dataset dataset) {
    int true_positive = 0 ;
    int *pred, **act = malloc(N*sizeof(int*)), i, j;
    FILE *fp;
    char buffer[BUFFER_SIZE], *value;

    for(int l = 0; l < N; l++) {
        act[l] = malloc(k*sizeof(int));
    }

    fp = fopen(filename, "r");

    if(!fp) {
        Heap *actual = brute_force(dataset, k, l2); 
        actual_solution(actual, filename, N, k);
        if (!(fp = fopen(filename, "r"))) {
            printf("Can't open file\n");
            fclose(fp);
            return -1.0;
        }
    }

    while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        value = strtok(buffer, ":");
        i = atoi(value);
        j = 0;
        value = strtok(NULL, ",\n");
        
        while(value != NULL) {
            act[i][j] = atoi(value);
            value = strtok(NULL, ",\n");
            j++;
        }
    }

    fclose(fp);

    for (int i=0 ; i<N ; i++){
        pred = heap_getIndexes(predicted[i]);
        for (int l=0 ; l<k ; l++){
            for (int j=0 ; j<k; j++){
                if (act[i][l] == pred[j]){
                    true_positive++;
                    break;
                }
            }
        }
    }

    for(int l = 0; l < N; l++) {
        free(act[l]);
    }
    free(act);


    return (double) (true_positive) / (double) (N * k) ;      
}