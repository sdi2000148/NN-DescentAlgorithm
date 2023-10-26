#include "heap.h"
#include "brutal.h"
#include "metrics.h"
#include "services.h"
#include "dataset.h"

double recall(Heap *actual, Heap *predicted, int N, int k);
double recall_new(char *filename, Heap *predicted, int N, int k, Dataset dataset);