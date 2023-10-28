#include "acutest.h"
#include "heap.h"

void test_initialize(void) {
    // Δημιουργούμε μια κενή λίστα 
	Heap heap;
    heap_initialize(&heap, 20);

	// Ελέγχουμε ότι δεν απέτυχε η malloc στην λίστα, και ότι
	TEST_CHECK(heap_getCapacity(heap) == 20);

	heap_free(heap);
}

void test_update(void) {
    // Δημιουργούμε μια κενή λίστα 
	Heap heap;
    heap_initialize(&heap, 20);

    int N = 100;
    int replaced = 0;

    for (int i = N; i < N + 21; i++) {
        if (i < N + 20) {
            TEST_CHECK(heap_update(heap, i, (double)i, &replaced) == 1);
            TEST_CHECK(replaced == -1);
        }
        else {
            TEST_CHECK(heap_update(heap, i, (double)i, &replaced) == 0);
            TEST_CHECK(replaced == -1);
        }
    }

    /*for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++ {}
        TEST_CHECK( heap_getIndex(heap, i) == N+i);
    }*/


    TEST_CHECK(heap_update(heap, 30, 30.0, &replaced) == 1);
    TEST_CHECK(replaced != -1);
    

	heap_free(heap);
}

void test_search(void) {
    Heap heap;
    int replaced;
    heap_initialize(&heap, 10);

    for (int i = 0; i < 10; i++) {
        heap_update(heap, i, (double)i, &replaced);
    }

    for (int i = 0; i < 10; i++) {
        TEST_CHECK(heap_search(heap, i) == 1);
    }
    
    TEST_CHECK(heap_search(heap, 28) == 0);

    heap_free(heap);
    
}

TEST_LIST = {
	{ "heap_initialize", test_initialize },
    { "heap_update", test_update },
    { "heap_search", test_search },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};