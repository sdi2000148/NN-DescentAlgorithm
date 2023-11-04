#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"


int seq_search(int value , int size , int *array);
List *reverse(Heap *heaps, int numberOfObjects);
int nn_update(Heap *B, int v, int u, double l, Avl *R);
void heap_free_all(Heap *heap, int N);
void avl_free_all(Avl *avls, int n);
void neighbours_free_all(int **neighbours, int n);
void actual_solution(int **neighbours, char *path, int N, int k);
int **getNeighbours(Heap *heaps, int N, int k);