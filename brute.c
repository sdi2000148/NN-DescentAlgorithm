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
#include "read.h"
#include "timer.h"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char *path, *solution, *output, *metr;
    Dataset dataset;
    float *numbersSigmod;
    double *rectNode, start, finish;
    int k, objects, type, **brute_solution;
    Metric metric;

    if(argc != 7) {
        printf("./brute [type] [dataset path] [metric] [k] [solution path] [output csv]\n");
        return 1;
    }

    type = atoi(argv[1]);
    path = argv[2];
    metr = argv[3];
    k = atoi(argv[4]);
    solution = argv[5];
    output = argv[6];

    if(strcmp(metr, "l2") == 0) {
        metric = l2;
    }
    else {
        printf("Given metric not supported\n");
        return 1;
    }

    if (type == 1){
        numbersSigmod = readSigmod(path, &dataset);
    }
    else if (type == 2){
        rectNode = readme(path, &dataset);
    }
    else{
        printf("Given type not supported\n");
        return 1;
    }

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
    fprintf(fp, "%d, %s, %d, %d, %s, %e\n",type, path, objects, k, metr, finish-start);
    fclose(fp);

    save_solution(brute_solution, solution, objects, k);

    if (type == 1){
        free(numbersSigmod);
    }
    else if (type == 2){
        free(rectNode);
    }
    dataset_free(dataset);
    free(brute_solution);
     
    return 0;
} 