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

// void readme(Dataset dataset, double *numbers) {
//     int row = 0, column, i = 0;
//     FILE *fp;
//     char buffer[BUFFER_SIZE], *value;
    

//     fp = fopen("Datasets/5k.RectNode.normal.ascii", "r");

    
    

//     if(!fp) {
//         printf("Can't open file\n");
//         fclose(fp);
//         return;
//     }

//     while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
//         value = strtok(buffer, " \t\n\r");
//         column = 0;

//         while(value != NULL) {
//             numbers[i] = strtod(value, NULL);
//             dataset_addFeature(dataset, row, column, &numbers[i]);
//             column++;
//             i++;
//             value = strtok(NULL, " \t\n\r");
//         }
//         row++;
//     }

//     fclose(fp);
    
// }

void readme(char *fileName, Dataset dataset, float *numbers) {
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
}



int main(void) { 
    clock_t start_time, end_time;
    Dataset dataset;
    float *numbers = malloc(OBJECTS*DIMENSIONS*sizeof(float));

    dataset_initialize(&dataset, OBJECTS, DIMENSIONS);

    readme("Datasets/00000020.bin",dataset, numbers);


    // start_time = clock();
    // Heap *actual = brute_force(dataset, K, l2);   // brute force
    // actual_solution(actual, "Solutions/00000020.10.txt", OBJECTS, K);
    // end_time = clock();
    // printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, K, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);


    /*start_time = clock();
    Heap *predicted_2 = nn_descentBetter(dataset, K, l2);
    end_time = clock();
    printf("nn descentBetter time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);*/


    //double rec = recall(actual, predicted_1, OBJECTS, K);
    //printf("recall nn_descent: %f\n",rec*100) ;
    double rec_new = recall_new("Solutions/00000020.10.txt", predicted_1, OBJECTS, K, dataset);
    printf("recall_new nn_descent: %f\n",rec_new*100) ;

    /*rec = recall(actual, predicted_2, OBJECTS, K);
    printf("recall nn_descentBetter: %f\n",rec*100) ;
    rec_new = recall_new("Solutions/5k.4.10.txt", predicted_2, OBJECTS, K);
    printf("recall_new nn_descent: %f\n",rec_new*100) ;*/


    dataset_free(dataset);
    //heap_free_all(actual, OBJECTS);
    heap_free_all(predicted_1, OBJECTS);
    //heap_free_all(predicted_2, OBJECTS);
    free(numbers);

    return 0;
}