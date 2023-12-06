#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "metrics.h"
#include "brute_force.h"
#include "recall.h"
#include "heap.h"
#include "list.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#include "timer.h"
#include "metrics.h"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *path, *solution, *output, *metr;
    Dataset dataset;
    double start, finish;
    int k, objects, **brute_solution;
    Metric metric;

    if(argc != 6) {
        printf("./brute [dataset path] [metric] [k] [solution path] [output csv]\n");
        return 1;
    }

    path = argv[1];
    metr = argv[2];
    k = atoi(argv[3]);
    solution = argv[4];
    output = argv[5];

    if(strcmp(metr, "l2") == 0) {
        metric = l2;
    }
    else {
        printf("Given metric not supported\n");
        return 1;
    }

    dataset_initialize_sigmod(&dataset, path);

    GET_TIME(start);
    brute_solution = brute_force(dataset, k, metric);
    GET_TIME(finish);

    objects = dataset_getNumberOfObjects(dataset);

    // writing to csv file
    FILE *fp;
    fp = fopen(output, "a");
    if (fp == NULL){
        perror(output);
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s, %d, %d, %s, %e\n", path, objects, k, metr, finish-start);
    fclose(fp);

    save_solution(brute_solution, solution, objects, k);

    dataset_free(dataset);
    free(brute_solution);
     
    return 0;
} 