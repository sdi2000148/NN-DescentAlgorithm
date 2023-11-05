#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recall.h"
#define BUFFER_SIZE 1024


double recall(int **actual, int **predicted,  int N, int k) {
    int true_positive = 0;

    for (int i=0 ; i<N ; i++) {
        for (int l=0 ; l<k ; l++) {
            for (int j=0 ; j<k; j++) {
                if (actual[i][l] == predicted[i][j]) { 
                    true_positive++; // number of similar values
                    break;
                }
            }
        }
    }
    return (double)(true_positive) / (double)(N * k);
}



double recall_file(char *filename, int **predicted, int N, int k) {
    double rec;
    char buffer[BUFFER_SIZE], *value;
    int **actual = malloc(N*sizeof(int*)), i, j;
    FILE *fp = fopen(filename, "r");    

    if(!fp) {
        printf("Can't open file\n");
        fclose(fp);
        return -1.0;
    }

    for(int i = 0; i < N; i++) 
        actual[i] = malloc(k*sizeof(int));

    while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        value = strtok(buffer, ":");
        i = atoi(value);
        j = 0;
        value = strtok(NULL, ",\n");
        
        while(value != NULL) {
            actual[i][j] = atoi(value);
            value = strtok(NULL, ",\n");
            j++;
        }
    }

    fclose(fp);

    rec = recall(actual, predicted, N, k);

    neighbours_free_all(actual, N);

    return rec;
}