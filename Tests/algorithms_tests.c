#include "acutest.h"
#include "brutal.h"
#include "dataset.h"
#include "services.h"
#include "metrics.h"


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

TEST_LIST = {
	{ "brute_force", test_brute_force },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};