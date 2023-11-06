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
#define BUFFER_SIZE 1024



// USED WITH CAUTION
void find_solutions(void) {
    char filename[BUFFER_SIZE], number[BUFFER_SIZE];
    clock_t start_time, end_time;
    Dataset dataset;
    double *numbersRect;
    float *numbersSigmod;
    int objects, **solution, k[] = {10, 20, 50, 100}, ks = sizeof(k)/sizeof(int);

    
    for(int i = 0; i < ks; i++) {
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
    }

    for(int i = 0; i < ks; i++) {
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
    }


    for(int i = 0; i < ks; i++) {
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
    }

    for(int i = 0; i < ks; i++) {
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
    }

    for(int i = 0; i < ks; i++) {
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
    }
}


// USED WITH CAUTION
void run_nn_descents(void) {
    char filename[BUFFER_SIZE], number[BUFFER_SIZE];
    clock_t start_time, end_time;
    Dataset dataset;
    double *numbersRect, rec;
    float *numbersSigmod;
    int objects, **solution, k[] = {10, 20, 50, 100}, ks = sizeof(k)/sizeof(int);

    
    for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/5k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent_LJ(dataset, k[i], l2_double);
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
    }

    for(int i = 0; i < ks; i++) {
        numbersRect = readme("Datasets/50k.RectNode.normal.ascii", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent_LJ(dataset, k[i], l2_double);
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
    }


    for(int i = 0; i < ks; i++) {
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
    }

    for(int i = 0; i < ks; i++) {
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
    }

    for(int i = 0; i < ks; i++) {
        numbersSigmod = readSigmod("Datasets/00010000-1.bin", &dataset);
        objects = dataset_getNumberOfObjects(dataset);
        start_time = clock();
        solution = nn_descent_LJ(dataset, k[i], l2);
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
    }
}

int main(void) {
    
    //find_solutions();
    //run_nn_descents();
     
    return 0;
}