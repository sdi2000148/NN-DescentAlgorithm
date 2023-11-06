#include "acutest.h"
#include "list.h"	

void test_initialize(void) {
	List list;
    list_initialize(&list);

	TEST_CHECK(list_head(list) == NULL);

	list_free(list);
}

void test_insert(void) {
	List list;
    list_initialize(&list);
	
	int N = 1000;				

	for (int i = 0; i < N; i++) {
		list_insert(list, i);

		TEST_CHECK(listnode_data(list_head(list)) == i);	
	}

	Listnode node = list_head(list);

	for (int i = N - 1; i >= 0; i--) {
		TEST_CHECK(listnode_data(node) == i);
		node = list_next(node);
	}

	list_free(list);
}


void test_remove(void) {
	List list;
    list_initialize(&list);

	int N = 1000;	

    TEST_CHECK(list_remove(list, 0) == 0);

	for (int i = 0; i < N; i++) {
		
		list_insert(list, i);
	}


	for (int i = N - 1; i >= 0; i--) {

		TEST_CHECK(list_remove(list, i) == 1);

        if (i > 0) TEST_CHECK(listnode_data(list_head(list)) == i - 1);
        else TEST_CHECK(list_head(list) == NULL);
	}

	for (int i = 0; i < N; i++) {
		
		list_insert(list, i);
	}	

	TEST_CHECK(list_remove(list, N - 1) == 1);

    Listnode node = list_head(list);
    for (int i = N - 2; i >= 0; i--) {
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }

    TEST_CHECK(list_remove(list, 300) == 1);


	node = list_head(list);
    for (int i = N - 2; i >= 0; i--) {
        if (i == 300) continue;
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }


	TEST_CHECK(list_remove(list, 0) == 1);


	node = list_head(list);
    for (int i = N - 2; i >= 1; i--) {
        if (i == 300) continue;
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }

    TEST_CHECK(list_remove(list, 1001) == 0);

	list_free(list);
}

TEST_LIST = {
	{ "list_initialize", test_initialize },
    { "list_insert", test_insert },
    { "list_remove", test_remove },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};