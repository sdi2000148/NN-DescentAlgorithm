#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
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
#define OBJECTS 20
#define DIMENSIONS 100
#define K 10

/*void nn_descent_10000(void) {
    double rec;
    int k = 10, **predicted_1;
    float *numbers;
    Dataset dataset;
    clock_t start_time, end_time;

    numbers = readSigmod("Datasets/00010000-4.bin", &dataset);

    // ελενχουμε την ακριβεια του nn_descentBetter με 10000 δεδομενα και εκτυπωνουμε τον χρονο του και του brute_force
    //αλλα και το scan rate 
    start_time = clock();
    predicted_1 = nn_descentBetter(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    rec = recall("Solutions/00010000-4.10.txt", predicted_1, k, dataset, l2);
    end_time = clock();
    printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("recall nn_descent: %f\n",rec*100) ;

    neighbours_free_all(predicted_1, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);

}


void nn_descent_5000(void) {
    double rec;
    int k = 10, **predicted_1;
    double *numbers;
    Dataset dataset;
    clock_t start_time, end_time;

    numbers = readme("Datasets/5k.RectNode.normal.ascii", &dataset);

    start_time = clock();
    predicted_1 = nn_descentBetter(dataset, k, l2_double);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    rec = recall("Solutions/5k.RectNode.normal.txt", predicted_1, k, dataset, l2_double);
    end_time = clock();
    printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("recall nn_descent: %f\n",rec*100) ;

    neighbours_free_all(predicted_1, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);
}*/



int main(void) {
    
    //nn_descent_5000();
    //nn_descent_10000();
     
    return 0;
}