#include "list.h"

typedef struct avl *Avl;


/* Initialize avl */
void avl_initialize(Avl *avl);

/* Insert value to avl, return 1 if succeeded, 0 if the value already existed */
int avl_insert(Avl avl, int value);

/* Remove value from avl, return 1 if succeeded, 0 if the value never existed */
int avl_remove(Avl avl, int value);

/* Search value in avl, return 1 if found, 0 otherwise */
int avl_search(Avl avl, int value);

/* Insert all the values of the avl to the list */
void avl_copyToList(Avl avl, List list);


void avl_findReverses(Avl *avls, int i, List *R);

/* Free memory of avl */
void avl_free(Avl avl);
