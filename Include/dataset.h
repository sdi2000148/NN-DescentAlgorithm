#include "common_types.h"

typedef struct dataset* Dataset;

typedef struct object* Object;


/* Initialize dataset with size numberOfObjects and dimensions */
void dataset_initialize(Dataset *dataset, int numberOfObjects, int dimensions);

/* Add feature in dataset to the object i, in the specified dimension, using pointer */
int dataset_addFeature(Dataset dataset, int i, int dimension, Pointer feature);

/* Get number of objects of dataset */
int dataset_getNumberOfObjects(Dataset dataset);

/* Get dimensions of dataset */
int dataset_getDimensions(Dataset dataset);

/* Get dataset feautre of object i in dimension specified */
Pointer dataset_getFeature(Dataset dataset, int i, int dimension);

/* Get all the dataset features of object i*/
Pointer *dataset_getFeatures(Dataset dataset, int i);

/* Free memory of dataset */
void dataset_free(Dataset dataset);



