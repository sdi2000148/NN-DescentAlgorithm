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

    nn_update(heaps, 0, 1, 16.4, R);
    nn_update(heaps, 0, 4, 15.6, R);
    nn_update(heaps, 1, 4, 10.0, R);
    nn_update(heaps, 1, 0, 16.4, R);
    nn_update(heaps, 2, 4, 19.4, R);
    nn_update(heaps, 2, 1, 11.4, R);
    nn_update(heaps, 3, 2, 12.4, R);
    nn_update(heaps, 3, 4, 15.4, R);
    nn_update(heaps, 4, 2, 17.4, R);
    nn_update(heaps, 4, 1, 19.4, R);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 1 && j == 2) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 2 && j == 3) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 0) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 3) TEST_CHECK(avl_search(R[i], j) == 1);
            else TEST_CHECK(avl_search(R[i], j) == 0);
        }
    }

    //Η περιπτωση οπου ο κομβος 4 που βγαινει έχει ακμη προς τον κομβο 2 που αλλαζουμε το heap του
    //αρα πρεπει να προσθεθει ο 4 στους reserves του 2
    //και ο κομβος 3 που μπαινει στο heap του 2 υπαρχρει στους reveres του 2
    //αρα θα πρεπει να αφαιρεθει απο τους reverses του 2  
    nn_update(heaps, 2, 3, 9.4, R);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 1 && j == 2) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 2 && j == 4) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 0) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 3) TEST_CHECK(avl_search(R[i], j) == 1);
            else TEST_CHECK(avl_search(R[i], j) == 0);
        }
    }

    //Η περιπτωση οπου ο κομβος 1 που βγαινει έχει ακμη προς τον κομβο 0 που αλλαζουμε το heap του
    //αρα πρεπει να προσθεθει ο 1 στους reserves του 0
    //και ο κομβος 3 που μπαινει στο heap του 0 δεν εχει στους reveres του τον 0
    //αρα θα πρεπει να προσθεθει στους reverses του ο 0 
    nn_update(heaps, 0, 3, 9.4, R);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0 && j == 1) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 1 && j == 2) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 2 && j == 4) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 3 && j == 0) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 0) TEST_CHECK(avl_search(R[i], j) == 1);
            else if (i == 4 && j == 3) TEST_CHECK(avl_search(R[i], j) == 1);
            else TEST_CHECK(avl_search(R[i], j) == 0);
        }
    }

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