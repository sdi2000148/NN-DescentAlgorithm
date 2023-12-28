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
    char *path, *solution, *output, *metr, *endptr;
    Dataset dataset;
    double p, d;
    double recall, start, finish;
    int k, objects, thread_count, **nn_solution;
    Metric metric;

    if(argc != 9) {
        printf("./main [dataset path] [metric] [k] [p] [d] [thread_count] [solution path] [output csv]\n");
        return 1;
    }

    path = argv[1];
    metr = argv[2];
    k = atoi(argv[3]);
    p = strtod(argv[4], &endptr);
    d = strtod(argv[5], &endptr);
    thread_count = atoi(argv[6]);
    solution = argv[7];
    output = argv[8];

    srand(time(NULL));

    dataset_initialize_sigmod(&dataset, path);

    if(strcmp(metr, "l2") == 0) {
        metric = l2;
    }
    else {
        printf("Given metric not supported\n");
        return 1;
    }
    
    dataset_calculateSquares(dataset);

    GET_TIME(start);
    if (thread_count == 1){
        nn_solution = nn_descent(dataset, metric, k, p, d);
    }
    else{
        nn_solution = nn_descent_parallel(dataset, metric, k, p, d, thread_count);
    }
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
    
    fprintf(fp, "%s,%d,%d,%.5f,%s,%.3f,%.5f,%d,%e\n", path, objects, k, recall, metr, p, d, thread_count, finish-start);
    fclose(fp);
    
    dataset_free(dataset);
    neighbours_free_all(nn_solution, objects);
     
    return 0;
} 