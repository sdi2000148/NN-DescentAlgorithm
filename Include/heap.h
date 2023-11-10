/*

Max-heap data structure:

Items are pairs of index-value. Value is used as basis for any comparison done
in the heap.

*/


typedef struct heap* Heap ;


// Initialize heap with size k 
void heap_initialize(Heap *hp, int k);


// return 1 if heap is full, 0 otherwise
int heap_full(Heap hp);


// return 1 if heap is empty, 0 otherwise
int heap_empty(Heap hp);


// remove root from heap 
// return index of removed item, otherwise return -1
int heap_remove(Heap hp);


// return 1 on change, 0 otherwise
int heap_update(Heap hp, int index, double value);


// print content of heap
void heap_print(Heap hp);


// free all memory reserved for heap
void heap_free(Heap hp);


// get max size of heap
int heap_getCapacity(Heap hp);


// get number of elements currently present in heap
int heap_getCount(Heap hp);


// get index of ith item in heap array (ITEMS ARE NOT SORTED!!!)
// return -1 when i is out of bounds
int heap_getIndex(Heap hp, int i);


// get value of ith item in heap array (ITEMS ARE NOT SORTED!!!)
// return -1.0 when i is out of bounds
double heap_getValue(Heap hp, int i);


// get flag of ith item in heap array (ITEMS ARE NOT SORTED!!!)
// return -1 when i is out of bounds
int heap_getFlag(Heap hp, int i);


// set flag of ith item in heap array to false (ITEMS ARE NOT SORTED!!!)
// return -1 when i is out of bounds, on success return 1
int heap_setFlag(Heap hp, int i);


// get index of root item 
int heap_getMaxIndex(Heap hp);


// get value of root item
double heap_getMaxValue(Heap hp);


// get flag of root item
int heap_getMaxFlag(Heap hp);


// return 1 if item with given index is found in heap, else return 0
int heap_search(Heap hp, int index);



