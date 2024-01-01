#include "dataset.h"
#include "heap.h"
#include "metrics.h"

/* Find the nn_descent solution of K-NN graph (with the usage of local join) given the dataset, the k and the metric */
int **nn_descent(Dataset dataset, Metric metric, int k, double p, double d);

int **nn_descent_parallel(Dataset dataset, Metric metric, int k, double p, double d, int thread_count, int init, int trees, int threshold_rtp);