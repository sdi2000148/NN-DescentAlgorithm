#include "list.h"

typedef struct heap* Heap ;

void heap_initialize(Heap *, int) ;
int heap_update(Heap, int, double) ; 
int nn_heap_update(Heap, int, int, double, List *) ; 
void heap_print(Heap) ;
void heap_free(Heap) ;
void heap_free_all(Heap *, int);
int *heap_getIndexes(Heap) ;
int heap_getCapacity(Heap) ;