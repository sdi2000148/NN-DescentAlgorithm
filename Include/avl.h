#include "list.h"

typedef struct avl *Avl;


/* Initialize avl */
void avl_initialize(Avl *avl);

/* Insert value to avl */
void avl_insert(Avl avl, int value);

/* Remove value from avl */
void avl_remove(Avl avl, int value);

/* Search value in avl, return 1 if found, 0 otherwise */
int avl_search(Avl avl, int value);

/* Insert all the values of the avl to the list */
void avl_copyToList(Avl avl, List list);

/* Free memory of avl */
void avl_free(Avl avl);
