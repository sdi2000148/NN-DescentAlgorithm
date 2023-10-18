#include "list.h"

typedef struct heap* Heap ;

void heap_initialize(Heap *, int) ;
void heap_print(Heap) ;
void heap_free(Heap) ;

int heap_update(Heap, int, double, int *) ; 
int heap_getCapacity(Heap) ;
int heap_search(Heap, int) ;

int *heap_getIndexes(Heap) ;

