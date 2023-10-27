#include "acutest.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "brutal.h"
#include "dataset.h"
#include "services.h"
#include "metrics.h"
#include "nn_descent.h"
#include "nng_initialization.h"
#include "recall.h"
#include "metrics.h"
#define BUFFER_SIZE 1024


void test_brute_force(void) {
    Dataset dataset;
    int dimensions = 2, objects = 5, k = 2;
    float *numbers = malloc(objects*dimensions*sizeof(float));

    dataset_initialize(&dataset, objects, dimensions);

    numbers[0] = 0.0; 
    dataset_addFeature(dataset, 0, 0, &numbers[0]);
    numbers[1] = 0.0; 
    dataset_addFeature(dataset, 0, 1, &numbers[1]);
    numbers[2] = 2.0; 
    dataset_addFeature(dataset, 1, 0, &numbers[2]);
    numbers[3] = 3.0; 
    dataset_addFeature(dataset, 1, 1, &numbers[3]);
    numbers[4] = -3.0; 
    dataset_addFeature(dataset, 2, 0, &numbers[4]);
    numbers[5] = 1.0; 
    dataset_addFeature(dataset, 2, 1, &numbers[5]);
    numbers[6] = -1.5; 
    dataset_addFeature(dataset, 3, 0, &numbers[6]);
    numbers[7] = -2.5; 
    dataset_addFeature(dataset, 3, 1, &numbers[7]);
    numbers[8] = 1.0; 
    dataset_addFeature(dataset, 4, 0, &numbers[8]);
    numbers[9] = -10.0; 
    dataset_addFeature(dataset, 4, 1, &numbers[9]);

    Heap *actual = brute_force(dataset, k, l2);

    TEST_CHECK(heap_search(actual[0], 2) == 1);
    TEST_CHECK(heap_search(actual[0], 3) == 1);
    TEST_CHECK(heap_search(actual[1], 0) == 1);
    TEST_CHECK(heap_search(actual[1], 2) == 1);
    TEST_CHECK(heap_search(actual[2], 0) == 1);
    TEST_CHECK(heap_search(actual[2], 3) == 1);
    TEST_CHECK(heap_search(actual[3], 0) == 1);
    TEST_CHECK(heap_search(actual[3], 2) == 1);
    TEST_CHECK(heap_search(actual[4], 0) == 1);
    TEST_CHECK(heap_search(actual[4], 3) == 1);
    
    dataset_free(dataset);
    heap_free_all(actual, objects);
    free(numbers);
}

void test_nng_initialization(void) {
    Dataset dataset;
    int dimensions = 2, objects = 5, k = 2, *indexes;
    float *numbers = malloc(objects*dimensions*sizeof(float));

    dataset_initialize(&dataset, objects, dimensions);

    numbers[0] = 0.0; 
    dataset_addFeature(dataset, 0, 0, &numbers[0]);
    numbers[1] = 0.0; 
    dataset_addFeature(dataset, 0, 1, &numbers[1]);
    numbers[2] = 2.0; 
    dataset_addFeature(dataset, 1, 0, &numbers[2]);
    numbers[3] = 3.0; 
    dataset_addFeature(dataset, 1, 1, &numbers[3]);
    numbers[4] = -3.0; 
    dataset_addFeature(dataset, 2, 0, &numbers[4]);
    numbers[5] = 1.0; 
    dataset_addFeature(dataset, 2, 1, &numbers[5]);
    numbers[6] = -1.5; 
    dataset_addFeature(dataset, 3, 0, &numbers[6]);
    numbers[7] = -2.5; 
    dataset_addFeature(dataset, 3, 1, &numbers[7]);
    numbers[8] = 1.0; 
    dataset_addFeature(dataset, 4, 0, &numbers[8]);
    numbers[9] = -10.0; 
    dataset_addFeature(dataset, 4, 1, &numbers[9]);

    List *R = malloc(dataset_getNumberOfObjects(dataset) * sizeof(List));

    Heap *heap = nng_initialization_random(dataset, k, l2, R);

    for (int i = 0; i < objects; i++) {
        indexes = heap_getIndexes(heap[i]);
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                if (l != j) TEST_CHECK(indexes[j] != indexes[l]);
            }
            TEST_CHECK(list_remove(R[i], indexes[j]) == 0);
        }
    }

    heap_free_all(heap, objects);
    dataset_free(dataset);
    for (int i = 0; i < objects; i++) {
        list_free(R[i]);
    }
    free(R);
    free(numbers);
}

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

void test_nn_descent_20(void) {

    Dataset dataset;
    int k = 10;

    clock_t start_time, end_time;
    float *numbers;

    numbers = readme("../Datasets/00000020.bin", &dataset);


    start_time = clock();
    Heap *predicted_1 = nn_descentBetter(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    double rec = recall("../Solutions/00000020.10.txt", predicted_1, dataset_getNumberOfObjects(dataset), k, dataset);
    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.95);

    heap_free_all(predicted_1, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);

}

void test_nn_descent_10000(void) {

    Dataset dataset;
    int k = 30;

    clock_t start_time, end_time;
    float *numbers;

    numbers = readme("../Datasets/00010000-4.bin", &dataset);


    start_time = clock();
    Heap *predicted_1 = nn_descentBetter(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    double rec = recall("../Solutions/00010000-4.100.txt", predicted_1, dataset_getNumberOfObjects(dataset), k, dataset);
    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.95);

    heap_free_all(predicted_1, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);

}

TEST_LIST = {
	{ "brute_force", test_brute_force },
    { "nng_initialization", test_nng_initialization },
    { "nn_descent_20", test_nn_descent_20},
    { "nn_descent_10000", test_nn_descent_10000},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};