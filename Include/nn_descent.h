#include "dataset.h"
#include "heap.h"

Heap * nn_descent(Dataset dataset, int k, Metric metric);

Heap * nn_descentBetter(Dataset dataset, int k, Metric metric);