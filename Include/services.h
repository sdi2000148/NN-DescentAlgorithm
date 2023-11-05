#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"


int seq_search(int value , int size , int *array);

List *reverse(Heap *heaps, int numberOfObjects);

/* Given a heap array B that contains the current edges of the graph, indexes v and u, a number l and the avl 
tree array of reverse neighbours R, try to add to the neighbours of v, u with distance l. If it succeeds, the 
current change is reflected to B and R. */
int nn_update(Heap *B, int v, int u, double l, Avl *R);


// take a knn graph (NxK array) and save it in a file defined by the path parameter
void save_solution(int **neighbours, char *path, int N, int k);


void heap_free_all(Heap *heap, int N);


void avl_free_all(Avl *avls, int n);


void neighbours_free_all(int **neighbours, int n);


int **getNeighbours(Heap *heaps, int N, int k);




