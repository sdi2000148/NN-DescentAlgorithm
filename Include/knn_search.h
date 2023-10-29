#include "dataset.h"
#include "heap.h"

int *search_knn(Dataset dataset, Heap *heap, Pointer *object, int k, Metric metric);
int *search_knn_brute_force(Dataset dataset, Pointer *object, int k, Metric metric);