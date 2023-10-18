#include "acutest.h"
#include "heap.h"

void test_initialize(void) {
    // Δημιουργούμε μια κενή λίστα 
	Heap heap;
    heap_initialize(&heap, 20);

	// Ελέγχουμε ότι δεν απέτυχε η malloc στην λίστα, και ότι
	TEST_ASSERT(heap_getCapacity(heap) == 20);

	heap_free(heap);
}

void test_insert(void) {
    // Δημιουργούμε μια κενή λίστα 
	Heap heap;
    heap_initialize(&heap, 20);

    int N = 100;
    int replaced = 0;

    for (int i = N; i < N + 21; i++) {
        if (i < N + 20) {
            TEST_ASSERT(heap_update(heap, i, (double)i, &replaced) == 1);
            TEST_ASSERT(replaced == -1);
        }
        else {
            TEST_ASSERT(heap_update(heap, i, (double)i, &replaced) == 0);
            TEST_ASSERT(replaced == -1);
        }
    }

    int *indeces = heap_getIndexes(heap);
    for (int i = 0; i < 20; i++) {
        TEST_ASSERT(indeces[i] == N+i);
    }


    TEST_ASSERT(heap_update(heap, 30, 30.0, &replaced) == 1);
    TEST_ASSERT(replaced != -1);
    

	heap_free(heap);
}

TEST_LIST = {
	{ "heap_initialize", test_initialize },
    { "heap_insert", test_insert },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};