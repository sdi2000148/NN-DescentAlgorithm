#include "dataset.h"

// searching for the knn of an object using the knn-graph
int *search_knn(Dataset dataset, int **graph, Pointer *object, int k, Metric metric);



// searching for the knn of an object through brute force
int *search_knn_brute_force(Dataset dataset, Pointer *object, int k, Metric metric);