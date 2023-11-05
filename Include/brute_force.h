#include "dataset.h"
#include "heap.h"


/* Find the brute force solution of K-NN graph given the dataset, the k and the metric */
int **brute_force(Dataset dataset, int k, Metric metric);