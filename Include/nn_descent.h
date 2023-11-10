#include "dataset.h"
#include "heap.h"

/* Find the nn_descent solution of K-NN graph (with the usage of local join) given the dataset, the k and the metric */
int **nn_descent(Dataset dataset, int k, Metric metric);