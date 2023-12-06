#include "dataset.h"

typedef float (*Metric)(Dataset dataset, int x, int y);

typedef float (*Metric_search)(Dataset dataset, int x, float *y);

float l2(Dataset dataset, int x, int y);

float l2_search(Dataset dataset, int x, float *y);