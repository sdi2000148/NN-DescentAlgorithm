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
    char *path, *solution, *output, *metr, *endptr;
    Dataset dataset;
    double p, d;
    float *numbersSigmod;
    double *rectNode, recall, start, finish;
    int k, objects, type, **nn_solution;
    Metric metric;

    if(argc != 9) {
        printf("./main [type] [dataset path] [metric] [k] [p] [d] [solution path] [output csv]\n");
        return 1;
    }

    type = atoi(argv[1]);
    path = argv[2];
    metr = argv[3];
    k = atoi(argv[4]);
    p = strtod(argv[5], &endptr);
    d = strtod(argv[6], &endptr);
    solution = argv[7];
    output = argv[8];

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
    nn_solution = nn_descent(dataset, metric, k, p, d);
    GET_TIME(finish);

    

    objects = dataset_getNumberOfObjects(dataset);
    recall = recall_file(solution, nn_solution, objects, k);

    // writing to csv file
    FILE *fp;
    fp = fopen(output, "a");
    if (fp == NULL){
        perror(output);
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%d, %s, %d, %d, %.5f, %s, %.3f, %.5f, %e\n",type, path, objects, k, recall, metr, p, d, finish-start);
    fclose(fp);

    // save_solution(nn_solution, solution, objects, k);

    if (type == 1){
        free(numbersSigmod);
    }
    else if (type == 2){
        free(rectNode);
    }
    dataset_free(dataset);
    free(nn_solution);
     
    return 0;
} 