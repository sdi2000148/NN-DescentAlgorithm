#include "dataset.h"

#include "heap.h"

#include "metrics.h"


/*Find the brute force solution of K-NN graph given the dataset, the k and the metric.
A N*k 2D array is returned. */
int ** brute_force(Dataset dataset, int k, Metric metric);