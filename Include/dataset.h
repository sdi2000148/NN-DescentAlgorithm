#include "common_types.h"

typedef struct dataset* Dataset;

typedef struct object* Object;



void dataset_initialize(Dataset *dataset, int numberOfObjects, int dimensions);
int dataset_addFeature(Dataset dataset, int i, int dimension, Pointer feature);
int dataset_getNumberOfObjects(Dataset dataset);
int dataset_getDimensions(Dataset dataset);
Pointer dataset_getFeature(Dataset dataset, int i, int dimension);
Pointer *dataset_getFeatures(Dataset dataset, int i);
void dataset_print(Dataset dataset);
void dataset_free(Dataset dataset);



