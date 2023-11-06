#include "recall.h"
#include "acutest.h"
#define N 10


void test_recall(void) {
    char *filename = "kojo.txt";
    int replaced, k = 10, **actual_n, **predicted_n;
    Heap actual[N], predicted[N];

    // 50% recall
    for (int i = 0; i < N; i++){
        heap_initialize(&actual[i], k);
        heap_initialize(&predicted[i], k);
        if ((i % 2) == 0) {
            for (int j = 0; j < k; j++) {
                heap_update(actual[i], j, (double)j, &replaced);
                heap_update(predicted[i], j, (double)j, &replaced);
            }
        }
        else {
            for (int j = 0; j < k; j++) {
                heap_update(actual[i], j, (double)j, &replaced);
                heap_update(predicted[i], j+N, (double)(j+N), &replaced);
            }
        }   
    }

    actual_n = getNeighbours(actual, N, k);
    predicted_n = getNeighbours(predicted, N, k);


    save_solution(actual_n, filename, N, k);
    

    TEST_CHECK(recall(actual_n, predicted_n, N, k) == 0.5);
    TEST_CHECK(recall_file(filename, predicted_n, N, k) == 0.5);
    
    for (int i = 0; i < N; i++) {
        heap_free(actual[i]);
        heap_free(predicted[i]);
    }

    neighbours_free_all(actual_n, N);
    neighbours_free_all(predicted_n, N);

    if(remove(filename) != 0) 
        printf("Error deleting the file %s\n", filename);
    
}

TEST_LIST = {
	{ "recall", test_recall },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};