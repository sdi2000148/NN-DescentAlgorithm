#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"

// perform sequential search in an array
// return 1 when item is found, or 0 otherwise
int seq_search(int value , int size , int *array);


// B represents the direct neighbors for each object.
// Compute the reverse neighbors and store then in R .
void reverse(List *B, List *R, int numberOfObjects);


// Same as reverse, but makes sure that a reverse neighbor
// is added if and only if it is not a direct neighbor.
// Heaps is used for fast searches of direct neighbors.
void strict_reverse(List *B, List *R, int numberOfObjects, Heap *heaps);


// Takes heaps where the direct neighbors of each object are stored and returns the knn graph as a N*k 2D array.
// For each object the neighbors are sorted from closest to furthest.
// NULL is returned in case of failure.
// Warning: heaps are not usable after this operation.
int **getNeighbours(Heap *heaps, int N, int k);


// Take a knn graph (N*k 2D array) and save it in a file defined by the path parameter
void save_solution(int **neighbours, char *path, int N, int k);


void heap_free_all(Heap *heap, int N);


void avl_free_all(Avl *avls, int n);


void neighbours_free_all(int **neighbours, int n);