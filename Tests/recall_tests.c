#include "recall.h"
#include "acutest.h"

void test_recall(void) {
    Heap actual[10], predicted[10];
    int replaced;

    for (int i = 0; i < 10; i++){
        heap_initialize(&actual[i], 10);
        heap_initialize(&predicted[i], 10);
        if ((i % 2) == 0) {
            for (int j = 0; j < 10; j++) {
                heap_update(actual[i], j, (double)j, &replaced);
                heap_update(predicted[i], j, (double)j, &replaced);
            }
        }
        else {
            for (int j = 0; j < 10; j++) {
                heap_update(actual[i], j, (double)j, &replaced);
                heap_update(predicted[i], j+10, (double)(j+10), &replaced);
            }
        }   
    }

    actual_solution(actual, "../Solutions/recall_test", 10, 10);

    Dataset dataset;
    dataset_initialize(&dataset, 10, 1);

    TEST_CHECK(recall("../Solutions/recall_test", predicted, 10, 10, dataset) == 0.5);
    
    for (int i = 0; i < 10; i++) {
        heap_free(actual[i]);
        heap_free(predicted[i]);
    }

    dataset_free(dataset);
    
}

TEST_LIST = {
	{ "recall", test_recall },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};