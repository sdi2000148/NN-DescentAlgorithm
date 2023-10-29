#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "metrics.h"
#include "brutal.h"
#include "recall.h"
#include "heap.h"
#include "list.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#include <time.h>
#define BUFFER_SIZE 1024
#define OBJECTS 20
#define DIMENSIONS 100
#define K 10


/*void readme(char *fileName, Dataset dataset, float *numbers) {
    int row = 0, column = 0, dimensions = 100;
    uint32_t N;
    int fp;
    

    fp = open(fileName ,O_RDONLY,0);
    

    if(fp == -1) {
        printf("Can't open file\n");
        close(fp);
        return;
    }

    if (read(fp, &N, sizeof(uint32_t) ) == 0) {
        printf("Can't read N (number of obects)\n");
        close(fp);
        return;
    }

    for (int i = 0; i < ((int)N * dimensions); i++) {

        if (read(fp, &numbers[i], sizeof(float)) == 0) {
            printf("Can't read float (item of obect)\n");
            close(fp);
            return;
        }

        dataset_addFeature(dataset, row, column, &numbers[i]);
        
        column++;
        if (column == dimensions) {
            column = 0;
            row++;
        }
    }

    close(fp);
}*/

float * readme(char *fileName, Dataset *dataset) {
    int row = 0, column = 0, dimensions = 100;
    uint32_t N;
    int fp;
    

    fp = open(fileName ,O_RDONLY,0);
    

    if(fp == -1) {
        printf("Can't open file\n");
        close(fp);
        return NULL;
    }

    if (read(fp, &N, sizeof(uint32_t) ) == 0) {
        printf("Can't read N (number of obects)\n");
        close(fp);
        return NULL;
    }

    float *numbers = malloc(N*dimensions*sizeof(float));

    dataset_initialize(dataset, N, dimensions);

    for (int i = 0; i < ((int)N * dimensions); i++) {

        if (read(fp, &numbers[i], sizeof(float)) == 0) {
            printf("Can't read float (item of obect)\n");
            close(fp);
            return numbers;
        }

        dataset_addFeature((*dataset), row, column, &numbers[i]);
        
        column++;
        if (column == dimensions) {
            column = 0;
            row++;
        }
    }

    close(fp);
    return numbers;
}



int main(void) { 
    Dataset dataset;
    int k = 5;

    clock_t start_time, end_time;
    float *numbers;

    numbers = readme("Datasets/00002000-1.bin", &dataset);


    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    double rec = recall("Solutions/00002000-4.30.txt", predicted_1, dataset_getNumberOfObjects(dataset), k, dataset);
    end_time = clock();
    printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("recall nn_descent: %f\n",rec*100) ;

    heap_free_all(predicted_1, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);

    return 0;
}