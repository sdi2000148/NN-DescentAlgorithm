#include "acutest.h"
#include "heap.h"

void test_initialize(void) {
	Heap heap;

    heap_initialize(&heap, 20);

	TEST_CHECK(heap_getCapacity(heap) == 20);
    TEST_CHECK(heap_getCount(heap) == 0);

	heap_free(heap);
}

void test_update(void) {
	Heap heap;
    heap_initialize(&heap, 20);

    int N = 100, temp;
    int replaced = 0;

    // insert items in heap until it is full
    for (int i = N; i < N + 20; i++) {
        TEST_CHECK(heap_update(heap, i, (double)i, &replaced) == 1);
        TEST_CHECK(replaced == -1);
    }

    // update must fail
    temp = N + 40;
    TEST_CHECK(heap_update(heap, temp, (double)temp, &replaced) == 0);
    TEST_CHECK(replaced == -1);

    // update must succeed 
    temp = N - 40;
    TEST_CHECK(heap_update(heap, temp, (double)temp, &replaced) == 1);
    TEST_CHECK(replaced == N+19);
    
	heap_free(heap);
}

void test_search(void) {
    Heap heap;
    int replaced;
    heap_initialize(&heap, 10);

    // fill heap
    for (int i = 0; i < 10; i++) {
        heap_update(heap, i, (double)i, &replaced);
    }
    
    // searching for elements present in heap
    for (int i = 0; i < 10; i++) {
        TEST_CHECK(heap_search(heap, i) == 1);
    }
    
    // searching for something not present in heap
    TEST_CHECK(heap_search(heap, 20) == 0);

    heap_free(heap);
}


void test_remove(void) {
    Heap heap;
    int replaced;

    heap_initialize(&heap, 10);

    // fill heap
    for (int i = 0; i < 10; i++) {
        heap_update(heap, i, (double)i, &replaced);
    }

    // check that elements are removed in the correct order
    for (int i = 9; i >= 0; i--) {
        TEST_CHECK(heap_remove(heap) == i);
    }

    // remove from empty heap
    TEST_CHECK(heap_remove(heap) == -1);
    
    heap_free(heap); 
}


TEST_LIST = {
	{ "heap_initialize", test_initialize },
    { "heap_search", test_search },
    { "heap_update", test_update },
    { "heap_remove", test_remove },
	{ NULL, NULL } 
};