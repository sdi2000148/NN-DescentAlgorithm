typedef struct heap* Heap ;

void heap_initialize(Heap *, int) ;
void heap_print(Heap) ;
void heap_free(Heap) ;

int heap_update(Heap, int, double, int *) ; 
int heap_getCapacity(Heap) ;
int heap_getCount(Heap) ;
int heap_getIndex(Heap, int) ;
int heap_search(Heap, int) ;

double heap_getValue(Heap, int); 