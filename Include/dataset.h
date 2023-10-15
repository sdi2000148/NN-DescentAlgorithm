#pragma once
#include "heap.h"

struct object {
    int *features;
};

typedef struct object* Object;

struct dataset {
    int dimensions;
    int numberOfObjects;
    Object *objects;
};

typedef struct dataset* Dataset;

typedef double (*Metric)(int *x, int *y, int d);

Dataset dataset_create(int dimensions, int numberOfObjects);
Heap* nng_initialization(Dataset dataset, int k, Metric metric);
void dataset_print(Dataset dataset);
void dataset_free(Dataset dataset);

