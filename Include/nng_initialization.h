#include "dataset.h"

#include "heap.h"

#include "list.h"

#include "avl.h"

#include "metrics.h"

#include <omp.h>


/* Initialization of random K-NN graph given the dataset, the k and the metric. */
Heap * nng_initialization_random(Dataset dataset, int k, Metric metric);

/* Initialization of K-NN graph with the use of random projection tree(s) given the dataset, 
the k, the metric, the number of trees to be created and the minimum threshold number of a leaf */
Heap * nng_initialization_rpt(Dataset dataset, Metric metric, int k, int trees, int threshold, omp_lock_t * locks);