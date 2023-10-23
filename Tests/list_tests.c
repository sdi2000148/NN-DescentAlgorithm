#include "acutest.h"
#include "list.h"	

void test_initialize(void) {
	// Δημιουργούμε μια κενή λίστα 
	List list;
    list_initialize(&list);

	// Ελέγχουμε ότι δεν απέτυχε η malloc στην λίστα, και ότι
	// αρχικοποιείται με head με NULL (δηλαδή χωρίς κόμβους)
	TEST_CHECK(list_head(list) == NULL);

	list_free(list);
}

void test_insert(void) {
	List list;
    list_initialize(&list);
	
	int N = 1000;				

	for (int i = 0; i < N; i++) {
		// Εισαγωγή στην αρχή
		list_insert(list, i);

		// Ελέγχουμε εάν ο πρώτος κόμβος περιέχει σαν τιμή τον δείκτη που μόλις κάναμε insert								
		TEST_CHECK(listnode_data(list_head(list)) == i);	
	}

	// Ελέγχουμε εάν τα στοιχεία έχουν μπει με την αντίστροφη σειρά
	Listnode node = list_head(list);

	for (int i = N - 1; i >= 0; i--) {
		TEST_CHECK(listnode_data(node) == i);
		node = list_next(node);
	}

	list_free(list);
}


void test_remove(void) {
	// Δημιουργία λίστας
	List list;
    list_initialize(&list);

	int N = 1000;	

    // Remove σε κενή λίστα 

    TEST_CHECK(list_remove(list, 0) == 0);

	// Χρησιμοποιούμε την insert για να γεμίσουμε την λίστα, αφού την έχουμε δοκιμάσει ήδη στην test_insert()
	for (int i = 0; i < N; i++) {
		
		list_insert(list, i);
	}


	for (int i = N - 1; i >= 0; i--) {
		// Διαγράφουμε απο την αρχή και ελέγχουμε εάν η τιμή του πρώτου κόμβου 
		// ήταν η ίδια με αυτή που κάναμε insert παραπάνω

		TEST_CHECK(list_remove(list, i) == 1);

		// Ελέγχουμε εάν η τιμή του πρώτου κόμβου είναι η ίδια με αυτή που κάναμε insert παραπάνω
        if (i > 0) TEST_CHECK(listnode_data(list_head(list)) == i - 1);
        else TEST_CHECK(list_head(list) == NULL);
	}

	// Ξαναγεμίζουμε την λίστα
	for (int i = 0; i < N; i++) {
		
		list_insert(list, i);
	}	

    // Δοκιμάζουμε την διαγραφή του πρωτου κομβου
	TEST_CHECK(list_remove(list, N - 1) == 1);

    Listnode node = list_head(list);
    for (int i = N - 2; i >= 0; i--) {
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }

	// Δοκιμάζουμε την διαγραφή ενδιάμεσου κόμβου
    TEST_CHECK(list_remove(list, 300) == 1);


	node = list_head(list);
    for (int i = N - 2; i >= 0; i--) {
        if (i == 300) continue;
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }


	// Δοκιμάζουμε την διαγραφή τελευταίου κόμβου
	TEST_CHECK(list_remove(list, 0) == 1);


	node = list_head(list);
    for (int i = N - 2; i >= 1; i--) {
        if (i == 300) continue;
        TEST_CHECK(listnode_data(node) == i);
        node = list_next(node);
    }

    // Δοκιμάζουμε να διαγράψουμε στοιχείο που δεν υπάρχει
    TEST_CHECK(list_remove(list, 1001) == 0);

	list_free(list);
}

TEST_LIST = {
	{ "list_initialize", test_initialize },
    { "list_insert", test_insert },
    { "list_remove", test_remove },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};