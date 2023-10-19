#include "dataset.h"
#include "heap.h"
#include "list.h"

List *reverse(Heap *heaps, int numberOfObjects);
int nn_update(Heap *B, int v, int u, double l, List *R);
void heap_free_all(Heap *heap, int N);