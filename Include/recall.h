#include "heap.h"
#include "brute_force.h"
#include "metrics.h"
#include "services.h"
#include "dataset.h"

double recall(char *filename, int **predicted, int N, int k, Dataset dataset, Metric metric);