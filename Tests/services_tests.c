#include "acutest.h"
#include "services.h"
#include "avl.h"

void test_nn_update(void) {
    Avl *R = malloc(5* sizeof(Avl));
    Heap *heaps = malloc(5 * (sizeof(Heap)));

    for (int i = 0; i < 5; i++) {
        avl_initialize(&R[i]);
        heap_initialize(&heaps[i], 2);
    }

    nn_update(heaps, 0, 1, 12.4, R);
    nn_update(heaps, 0, 4, 15.6, R);
    nn_update(heaps, 1, 4, 10.0, R);
    nn_update(heaps, 1, 0, 16.4, R);
    nn_update(heaps, 2, 4, 19.4, R);
    nn_update(heaps, 2, 1, 11.4, R);
    nn_update(heaps, 3, 2, 12.4, R);
    nn_update(heaps, 3, 4, 15.4, R);
    nn_update(heaps, 4, 2, 17.4, R);
    nn_update(heaps, 4, 1, 19.4, R);

    TEST_CHECK(avl_search(R[0], 0) == 0);
    TEST_CHECK(avl_search(R[0], 1) == 0);
    TEST_CHECK(avl_search(R[0], 2) == 0);
    TEST_CHECK(avl_search(R[0], 3) == 0);
    TEST_CHECK(avl_search(R[0], 4) == 0);

    TEST_CHECK(avl_search(R[1], 0) == 0);
    TEST_CHECK(avl_search(R[1], 1) == 0);
    TEST_CHECK(avl_search(R[1], 2) == 1);
    TEST_CHECK(avl_search(R[1], 3) == 0);
    TEST_CHECK(avl_search(R[1], 4) == 0);

    TEST_CHECK(avl_search(R[2], 0) == 0);
    TEST_CHECK(avl_search(R[2], 1) == 0);
    TEST_CHECK(avl_search(R[2], 2) == 0);
    TEST_CHECK(avl_search(R[2], 3) == 1);
    TEST_CHECK(avl_search(R[2], 4) == 0);

    TEST_CHECK(avl_search(R[3], 0) == 0);
    TEST_CHECK(avl_search(R[3], 1) == 0);
    TEST_CHECK(avl_search(R[3], 2) == 0);
    TEST_CHECK(avl_search(R[3], 3) == 0);
    TEST_CHECK(avl_search(R[3], 4) == 0);

    TEST_CHECK(avl_search(R[4], 0) == 1);
    TEST_CHECK(avl_search(R[4], 1) == 0);
    TEST_CHECK(avl_search(R[4], 2) == 0);
    TEST_CHECK(avl_search(R[4], 3) == 1);
    TEST_CHECK(avl_search(R[4], 4) == 0);


    nn_update(heaps, 2, 3, 9.4, R);

    TEST_CHECK(avl_search(R[0], 0) == 0);
    TEST_CHECK(avl_search(R[0], 1) == 0);
    TEST_CHECK(avl_search(R[0], 2) == 0);
    TEST_CHECK(avl_search(R[0], 3) == 0);
    TEST_CHECK(avl_search(R[0], 4) == 0);

    TEST_CHECK(avl_search(R[1], 0) == 0);
    TEST_CHECK(avl_search(R[1], 1) == 0);
    TEST_CHECK(avl_search(R[1], 2) == 1);
    TEST_CHECK(avl_search(R[1], 3) == 0);
    TEST_CHECK(avl_search(R[1], 4) == 0);

    TEST_CHECK(avl_search(R[2], 0) == 0);
    TEST_CHECK(avl_search(R[2], 1) == 0);
    TEST_CHECK(avl_search(R[2], 2) == 0);
    TEST_CHECK(avl_search(R[2], 3) == 0);
    TEST_CHECK(avl_search(R[2], 4) == 1);

    TEST_CHECK(avl_search(R[3], 0) == 0);
    TEST_CHECK(avl_search(R[3], 1) == 0);
    TEST_CHECK(avl_search(R[3], 2) == 0);
    TEST_CHECK(avl_search(R[3], 3) == 0);
    TEST_CHECK(avl_search(R[3], 4) == 0);

    TEST_CHECK(avl_search(R[4], 0) == 1);
    TEST_CHECK(avl_search(R[4], 1) == 0);
    TEST_CHECK(avl_search(R[4], 2) == 0);
    TEST_CHECK(avl_search(R[4], 3) == 1);
    TEST_CHECK(avl_search(R[4], 4) == 0);

    for (int i = 0; i < 5; i++) {
        avl_free(R[i]);
        heap_free(heaps[i]);
    }
    free(R);
    free(heaps);
    
}

TEST_LIST = {
	{ "nn_update", test_nn_update },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};