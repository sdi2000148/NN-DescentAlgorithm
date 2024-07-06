/*

Max-heap data structure:

Items are triplets of index-value-flag. Value is used as basis for any comparison done
in the heap.

Every time a new item is inserted in the heap, its the flag is set to 1

*/

typedef struct heap * Heap;

/* Initialize heap with size k */
void heap_initialize(Heap * hp, int k);

/* Return 1 if heap is full, 0 otherwise */
int heap_full(Heap hp);

/* Return 1 if heap is empty, 0 otherwise */
int heap_empty(Heap hp);

/* Remove root from heap return index of removed item, otherwise return -1 */
int heap_remove(Heap hp);

/* Return 1 on change, 0 otherwise */
int heap_update(Heap hp, int index, float value);

/* Print content of heap */
void heap_print(Heap hp);

/* Free all memory reserved for heap */
void heap_free(Heap hp);

/* Get max size of heap */
int heap_getCapacity(Heap hp);

/* Get number of elements currently present in heap */
int heap_getCount(Heap hp);

/* Get index of ith item in heap array (ITEMS ARE NOT SORTED!!!). 
Return -1 when i is out of bounds. */
int heap_getIndex(Heap hp, int i);

/* Get value of ith item in heap array (ITEMS ARE NOT SORTED!!!).
Return -1.0 when i is out of bounds. */
float heap_getValue(Heap hp, int i);

/* Get flag of ith item in heap array (ITEMS ARE NOT SORTED!!!).
Return -1 when i is out of bounds. */
int heap_getFlag(Heap hp, int i);

/* Set flag of ith item in heap array to false (ITEMS ARE NOT SORTED!!!).
Return -1 when i is out of bounds, else return 1 on success. */
int heap_setFlag(Heap hp, int i);

/* Get index of root item, or -1 when heap is empty */
int heap_getMaxIndex(Heap hp);

/* Get value of root item, or -1.0 when heap is empty */
float heap_getMaxValue(Heap hp);

/* Get flag of root item, or -1 when heap is empty */
int heap_getMaxFlag(Heap hp);

/* Return 1 if item with given index is found in heap, else return 0 */
int heap_search(Heap hp, int index);