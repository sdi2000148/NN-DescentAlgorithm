#include "acutest.h"
#include "read.h"
#include "brute_force.h"
#include "dataset.h"
#include "services.h"
#include "metrics.h"
#include "nn_descent.h"
#include "nng_initialization.h"
#include "recall.h"
#include "metrics.h"
#include "knn_search.h"
#define BUFFER_SIZE 1024


void test_brute_force(void) {
    int dimensions = 2, objects = 5, k = 2, **actual;
    float *numbers = malloc(objects*dimensions*sizeof(float));
    Dataset dataset;

    dataset_initialize(&dataset, objects, dimensions);

    //Δημιουργούμε ενα dataset και ελενχουμε αν η λυση ειναι ιδια με αυτη που υπολογισαμε με το χερι
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
    free(numbers);
}

void test_nng_initialization(void) {
    int dimensions = 2, objects = 5, k = 2;
    float *numbers = malloc(objects*dimensions*sizeof(float));
    Avl *R = malloc(objects * sizeof(Avl)), *avls = malloc(objects * sizeof(Avl));
    Dataset dataset;
    Heap *heap;


    //Δημιουργούμε ενα dataset
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

    heap = nng_initialization_random(dataset, k, l2, R, avls);

    //ελενχουμε οτι δεν το καθε heap δεν εχει διπλοτυπα και οτι κανες κομβος δεν εχει τον εαυτο του ως κοντινο
    for (int i = 0; i < objects; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                if (l != j) TEST_CHECK(heap_getIndex(heap[i], j) != heap_getIndex(heap[i], l));
                TEST_CHECK(heap_getIndex(heap[i], j) != i);
            }
        }
    }

    avl_free_all(R, objects);
    avl_free_all(avls, objects);
    heap_free_all(heap, objects);
    dataset_free(dataset);
    free(numbers);
}


void test_nn_descent_20(void) {
    double rec;
    Dataset dataset;
    int **actual, k = 10, objects, **predicted;
    float *numbers;
    clock_t start_time, end_time;
    

    numbers = readSigmod("../Datasets/00000020.bin", &dataset);
    objects = dataset_getNumberOfObjects(dataset);

    // ελενχουμε την ακριβεια του nn_descent και εκτυπωνουμε τον χρονο του και του brute_force
    //αλλα και το scan rate 
    start_time = clock();
    predicted = nn_descent(dataset, k, l2);
    end_time = clock();
    printf("nn descent time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    
    actual = brute_force(dataset, k, l2);

    rec = recall(actual, predicted, objects, k);

    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.85);

    neighbours_free_all(predicted, objects);
    neighbours_free_all(actual, objects);
    dataset_free(dataset);
    free(numbers);

}

void test_nn_descent_20_LJ(void) {
    double rec;
    Dataset dataset;
    int **actual, k = 10, objects, **predicted;
    float *numbers;
    clock_t start_time, end_time;
    

    numbers = readSigmod("../Datasets/00000020.bin", &dataset);
    objects = dataset_getNumberOfObjects(dataset);

    // ελενχουμε την ακριβεια του nn_descent και εκτυπωνουμε τον χρονο του και του brute_force
    //αλλα και το scan rate 
    start_time = clock();
    predicted = nn_descent_LJ(dataset, k, l2);
    end_time = clock();
    printf("nn descent LJ time: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    
    actual = brute_force(dataset, k, l2);

    rec = recall(actual, predicted, objects, k);

    printf("recall nn_descent: %f\n",rec*100) ;

    TEST_CHECK(rec >= 0.85);

    neighbours_free_all(predicted, objects);
    neighbours_free_all(actual, objects);
    dataset_free(dataset);
    free(numbers);

}



void test_search(void)
{
    Dataset dataset;
    int k = 5, object = 10, matches = 0;
    int *solution, *brute_force_solution;
    float *numbers;

    numbers = readSigmod("../Datasets/00000020.bin", &dataset);

    // using knn graph for searching
    int **actual = brute_force(dataset, k, l2);
    solution = search_knn(dataset, actual, dataset_getFeatures(dataset, object), k, l2);

    // using brute force
    brute_force_solution = search_knn_brute_force(dataset, dataset_getFeatures(dataset, object), k, l2);

    for (int i=0 ; i<k ; i++){
       for (int j=0 ; j<k ; j++){
        if (solution[i] == brute_force_solution[j]){
            matches++;
            break;
        }
       }
    }

    TEST_CHECK(matches == k);

    neighbours_free_all(actual, dataset_getNumberOfObjects(dataset));
    dataset_free(dataset);
    free(numbers);
    free(solution);
    free(brute_force_solution);
}





TEST_LIST = {
	{ "brute_force", test_brute_force },
    { "searching knn", test_search },
    { "nng_initialization", test_nng_initialization },
    { "nn_descent_20", test_nn_descent_20},
    { "nn_descent_20 local join", test_nn_descent_20_LJ},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};