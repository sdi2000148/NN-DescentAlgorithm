#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recall.h"
#define BUFFER_SIZE 1024

double recall(char *filename, int **predicted, int k, Dataset dataset, Metric metric) {
    int N = dataset_getNumberOfObjects(dataset), **act = malloc(N*sizeof(int*)), i, j, true_positive = 0;
    char buffer[BUFFER_SIZE], *value;
    int **actual;
    FILE *fp;

    for(int l = 0; l < N; l++) {
        act[l] = malloc(k*sizeof(int));
    }

    fp = fopen(filename, "r");

    if(!fp) {
        actual = brute_force(dataset, k, metric); 
        save_solution(actual, filename, N, k);
        if (!(fp = fopen(filename, "r"))) {
            printf("Can't open file\n");
            fclose(fp);
            return -1.0;
        }
        neighbours_free_all(actual, N);
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

    for (int i=0 ; i<N ; i++) {
        for (int l=0 ; l<k ; l++) {
            for (int j=0 ; j<k; j++) {
                if (act[i][l] == predicted[i][j]) { 
                    true_positive++; // number of similar values
                    break;
                }
            }
        }
    }

    for(int l = 0; l < N; l++) {
        free(act[l]);
    }
    free(act);

    return (double)(true_positive) / (double)(N * k) ;      
}