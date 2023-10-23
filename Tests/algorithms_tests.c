#include "acutest.h"
#include "brutal.h"
#include "dataset.h"
#include "services.h"
#include "metrics.h"
#include "nn_descent.h"
#include "nng_initialization.h"
#include "recall.h"
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

void readme(Dataset dataset, double *numbers) {
    int row = 0, column, i = 0;
    FILE *fp;
    char buffer[BUFFER_SIZE], *value;
    

    fp = fopen("Datasets/5k.RectNode.normal.ascii", "r");
    

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
    int dimensions = 2, objects = 5, k = 2;

    clock_t start_time, end_time;
    double *numbers = malloc(objects*dimensions*sizeof(double));

    dataset_initialize(&dataset, objects, dimensions);

    readme(dataset, numbers);


    start_time = clock();
    Heap *actual = brute_force(dataset, k, l2);   // brute force
    end_time = clock();
    printf("brute force time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    Heap *predicted_1 = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);


    start_time = clock();

    double rec = recall(actual, predicted_1, objects, k);
    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.95);

    dataset_free(dataset);
    heap_free_all(actual, objects);
    heap_free_all(predicted_1, objects);
    free(numbers);

}

TEST_LIST = {
	{ "brute_force", test_brute_force },
	{ "nn_descent", test_nn_descent },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};