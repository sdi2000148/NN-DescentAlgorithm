#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"

//List *reverse(Heap *heaps, int numberOfObjects);
int nn_update(Heap *B, int v, int u, double l, Avl *R);
void heap_free_all(Heap *heap, int N);
void actual_solution(Heap *heaps, char *path, int N, int k);