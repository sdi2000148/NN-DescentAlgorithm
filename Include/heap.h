typedef struct heap* Heap ;

void heap_initialize(Heap *, int) ;
int heap_update(Heap, int, double) ; 
void heap_print(Heap) ;
void heap_free(Heap) ;
void heap_free_all(Heap *, int);
int *heap_getIndexes(Heap) ;
int heap_getCapacity(Heap) ;