#include "acutest.h"
#include "brute_force.h"
#include "dataset.h"
#include "services.h"
#include "metrics.h"
#include "nn_descent.h"
#include "nng_initialization.h"
#include "recall.h"
#include "metrics.h"
#include "knn_search.h"
#include "omp.h"
#define BUFFER_SIZE 1024


void test_brute_force(void) {
    int dimensions = 2, objects = 5, k = 2, **actual;
    Dataset dataset;

    dataset_initialize(&dataset, objects, dimensions);

    dataset_addFeature(dataset, 0, 0, 0.0);
    dataset_addFeature(dataset, 0, 1, 0.0);
    dataset_addFeature(dataset, 1, 0, 2.0);
    dataset_addFeature(dataset, 1, 1, 3.0);
    dataset_addFeature(dataset, 2, 0, -3.0);
    dataset_addFeature(dataset, 2, 1, 1.0);
    dataset_addFeature(dataset, 3, 0, -1.5);
    dataset_addFeature(dataset, 3, 1, -2.5);
    dataset_addFeature(dataset, 4, 0, 1.0);
    dataset_addFeature(dataset, 4, 1, -10.0);

    dataset_calculateSquares(dataset);

    actual = brute_force(dataset, k, l2);

    TEST_CHECK(seq_search(2, k, actual[0]) == 1);
    TEST_CHECK(seq_search(3, k, actual[0]) == 1);
    TEST_CHECK(seq_search(0, k, actual[1]) == 1);
    TEST_CHECK(seq_search(2, k, actual[1]) == 1);
    TEST_CHECK(seq_search(0, k, actual[2]) == 1);
    TEST_CHECK(seq_search(3, k, actual[2]) == 1);
    TEST_CHECK(seq_search(0, k, actual[3]) == 1);
    TEST_CHECK(seq_search(2, k, actual[3]) == 1);
    TEST_CHECK(seq_search(0, k, actual[4]) == 1);
    TEST_CHECK(seq_search(3, k, actual[4]) == 1);
    
    dataset_free(dataset);
    neighbours_free_all(actual, objects);
}

void test_nng_initialization(void) {
    int dimensions = 2, objects = 5, k = 2;
    Dataset dataset;
    Heap *heap;

    dataset_initialize(&dataset, objects, dimensions);

    dataset_addFeature(dataset, 0, 0, 0.0);
    dataset_addFeature(dataset, 0, 1, 0.0);
    dataset_addFeature(dataset, 1, 0, 2.0);
    dataset_addFeature(dataset, 1, 1, 3.0);
    dataset_addFeature(dataset, 2, 0, -3.0);
    dataset_addFeature(dataset, 2, 1, 1.0);
    dataset_addFeature(dataset, 3, 0, -1.5);
    dataset_addFeature(dataset, 3, 1, -2.5);
    dataset_addFeature(dataset, 4, 0, 1.0);
    dataset_addFeature(dataset, 4, 1, -10.0);

    dataset_calculateSquares(dataset);

    heap = nng_initialization_random(dataset, k, l2);

    for (int i = 0; i < objects; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                if (l != j) TEST_CHECK(heap_getIndex(heap[i], j) != heap_getIndex(heap[i], l));
                TEST_CHECK(heap_getIndex(heap[i], j) != i);
            }
        }
    }

    heap_free_all(heap, objects);
    dataset_free(dataset);
}


void test_nn_descent_20(void) {
    double rec;
    Dataset dataset;
    int **actual, k = 10, objects, **predicted;
    float p = 0.4, d = 0.001;
    

    dataset_initialize_sigmod(&dataset, "../Datasets/00000020.bin");
    objects = dataset_getNumberOfObjects(dataset);

    dataset_calculateSquares(dataset);

    predicted = nn_descent(dataset, l2, k, p, d);
    
    actual = brute_force(dataset, k, l2);

    rec = recall(actual, predicted, objects, k);

    TEST_CHECK(rec >= 0.4);

    neighbours_free_all(predicted, objects);
    neighbours_free_all(actual, objects);
    dataset_free(dataset);

}


void test_search(void)
{
    Dataset dataset;
    int k = 5, object = 10, matches = 0;
    int *solution, *brute_force_solution;

    dataset_initialize_sigmod(&dataset, "../Datasets/00000020.bin");

    dataset_calculateSquares(dataset);

    // using knn graph for searching
    int **actual = brute_force(dataset, k, l2);
    solution = search_knn(dataset, actual, dataset_getFeatures(dataset, object), k, l2_search);

    // using brute force
    brute_force_solution = search_knn_brute_force(dataset, dataset_getFeatures(dataset, object), k, l2_search);

    for (int i=0 ; i<k ; i++){
       for (int j=0 ; j<k ; j++){
            if (solution[i] == brute_force_solution[j]){
                matches++;
                break;
            }
       }
    }

    neighbours_free_all(actual, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(solution);
    free(brute_force_solution);
}

void test_rpt(void) {
    Dataset dataset;
    int threshold = 2, k = 2, trees = 4;
    int **actual, objects, **predicted; 
    Heap *heaps;
    double rec;

    dataset_initialize_sigmod(&dataset, "../Datasets/00000020.bin");
    dataset_calculateSquares(dataset);
    objects = dataset_getNumberOfObjects(dataset);

    omp_lock_t *locks = malloc(objects * sizeof(omp_lock_t));
    for(int i = 0; i < objects; i++) {
        omp_init_lock(&locks[i]);
    }

#   pragma omp parallel 
    heaps = nng_initialization_rpt(dataset, l2, k, trees, threshold, locks);
    predicted = getNeighbours(heaps, objects, k);
    actual = brute_force(dataset, k, l2);
    rec = recall(actual, predicted, objects, k);
    printf("%f\n", rec);
    TEST_CHECK(rec >= 0.4);

    neighbours_free_all(predicted, objects);
    neighbours_free_all(actual, objects);
    dataset_free(dataset);
    for(int i = 0; i < objects; i++) {
        heap_free(heaps[i]);
        omp_destroy_lock(&locks[i]);
    }
    free(locks);
    free(heaps);
}





TEST_LIST = {
	{ "brute_force", test_brute_force },
    { "searching knn", test_search },
    { "nng_initialization", test_nng_initialization },
    { "nn_descent_20", test_nn_descent_20},
    { "rpt_20", test_rpt},
    { "test_rpt", test_rpt},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};