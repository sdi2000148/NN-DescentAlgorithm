#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"


int seq_search(int value , int size , int *array);

void reverse(Avl *avls, List *R, int numberOfObjects);

// take a knn graph (NxK array) and save it in a file defined by the path parameter
void save_solution(int **neighbours, char *path, int N, int k);


void heap_free_all(Heap *heap, int N);


void avl_free_all(Avl *avls, int n);


void neighbours_free_all(int **neighbours, int n);


int **getNeighbours(Heap *heaps, int N, int k);




