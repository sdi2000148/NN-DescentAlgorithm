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
    double *numbers = malloc(objects*dimensions*sizeof(double));

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
    double *numbers = malloc(objects*dimensions*sizeof(double));

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

void test_nn_descent_20(void) {

    Dataset dataset;
    int dimensions = 100, objects = 20, k = 10;

    clock_t start_time, end_time;
    float *numbers = malloc(objects*dimensions*sizeof(float));

    dataset_initialize(&dataset, objects, dimensions);

    readme("../Datasets/00000020.bin", dataset, numbers);


    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    double rec = recall_new("../Solutions/00000020.10.txt", predicted_1, objects, k, dataset);
    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.95);

    dataset_free(dataset);
    heap_free_all(predicted_1, objects);
    free(numbers);

}

void readme_old(Dataset dataset, double *numbers) {
    int row = 0, column, i = 0;
    FILE *fp;
    char buffer[BUFFER_SIZE], *value;
    

    fp = fopen("../Datasets/5k.RectNode.normal.ascii", "r");

    
    

    if(!fp) {
        printf("Can't open file\n");
        fclose(fp);
        return;
    }

    while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        value = strtok(buffer, " \t\n\r");
        column = 0;

        while(value != NULL) {
            numbers[i] = strtod(value, NULL);
            dataset_addFeature(dataset, row, column, &numbers[i]);
            column++;
            i++;
            value = strtok(NULL, " \t\n\r");
        }
        row++;
    }

    fclose(fp);
    
}


void test_nn_descent(void) {

    Dataset dataset;
    int dimensions = 4, objects = 5088, k = 10;

    clock_t start_time, end_time;
    double *numbers = malloc(objects*dimensions*sizeof(double));

    dataset_initialize(&dataset, objects, dimensions);

    readme_old(dataset, numbers);


    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    double rec = recall_new("../Solutions/5k.4.10.txt", predicted_1, objects, k, dataset);
    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.95);

    dataset_free(dataset);
    heap_free_all(predicted_1, objects);
    free(numbers);

}

TEST_LIST = {
	{ "brute_force", test_brute_force },
    { "nng_initialization", test_nng_initialization },
	{ "nn_descent", test_nn_descent },
    { "nn_descent_20", test_nn_descent_20},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};