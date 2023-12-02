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



// USED WITH CAUTION
void find_solutions(void) {
    /*char filename[BUFFER_SIZE], number[BUFFER_SIZE];
    clock_t start_time, end_time;
    Dataset dataset;
    double *numbersRect;
    float *numbersSigmod;
    int objects, **solution, k[] = {10, 20, 50, 100}, ks = sizeof(k)/sizeof(int);*/

    
    /*for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/5k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2_double);
        end_time = clock();
        printf("Brute force time 5k.RectNode with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/5k.RectNode.normal.ascii.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersRect);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/50k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2_double);
        end_time = clock();
        printf("Brute force time 50k.RectNode with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/50k.RectNode.normal.ascii.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersRect);
    }*/


    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00002000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2);
        end_time = clock();
        printf("Brute force time 00002000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00002000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00005000-3.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2);
        end_time = clock();
        printf("Brute force time 00005000-3.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00005000-3.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00010000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2);
        end_time = clock();
        printf("Brute force time 00010000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00010000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00050000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = brute_force(dataset, k[i], l2);
        end_time = clock();
        printf("Brute force time 00050000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00050000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        save_solution(solution, filename, objects, k[i]);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/
}


// USED WITH CAUTION
void run_nn_descents(void) {
    /*char filename[BUFFER_SIZE], number[BUFFER_SIZE];
    clock_t start_time, end_time;
    Dataset dataset;
    double *numbersRect, rec;
    float *numbersSigmod, p = 0.4, d = 0.001;
    int objects, **solution, k[] = {10, 20, 50, 100}, ks = sizeof(k)/sizeof(int);*/

    
    /*for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/5k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent(dataset, k[i], l2_double);
        end_time = clock();
        printf("NN descent LJ time 5k.RectNode with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/5k.RectNode.normal.ascii.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersRect);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/50k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent(dataset, k[i], l2_double);
        end_time = clock();
        printf("NN descent LJ time 50k.RectNode with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/50k.RectNode.normal.ascii.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersRect);
    }*/


    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00002000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent_LJ(dataset, k[i], l2);
        end_time = clock();
        printf("NN descent LJ time 00002000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00002000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00005000-3.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent_LJ(dataset, k[i], l2);
        end_time = clock();
        printf("NN descent time 00005000-3.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00005000-3.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00010000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent(dataset, k[i], l2);
        end_time = clock();
        printf("Brute force time 00010000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00010000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/

    /*for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00050000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent(dataset, l2, k[i], p, d);
        end_time = clock();
        printf("Brute force time 00050000-1.bin with k=%d:%f\n", k[i], (double)(end_time - start_time) / CLOCKS_PER_SEC);
        strcpy(filename, "Solutions/00050000-1.");
        sprintf(number, "%d", k[i]);
        strcat(filename, number);
        strcat(filename, ".txt");
        rec = recall_file(filename, solution, objects, k[i]);
        printf("Recall:%f\n", rec);
        neighbours_free_all(solution, objects);
        dataset_free(dataset);
        free(numbersSigmod);
    }*/
}

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