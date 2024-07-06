typedef struct dataset * Dataset;

/* Initialize dataset with size numberOfObjects and dimensions */
void dataset_initialize_sigmod(Dataset * dataset, char * path);

void dataset_initialize(Dataset * dataset, int N, int dimensions);

int dataset_addFeature(Dataset dataset, int i, int dimension, float feature);

/* Get number of objects in dataset */
int dataset_getNumberOfObjects(Dataset dataset);

/* Get dimensions of the objects in dataset */
int dataset_getDimensions(Dataset dataset);

/* Get dataset feautre of object i in dimension specified */
float dataset_getFeature(Dataset dataset, int i, int dimension);

/* Get dataset feautres of object i */
float * dataset_getFeatures(Dataset dataset, int i);

/* Calculate the square sum for every object in the dataset */
void dataset_calculateSquares(Dataset dataset);

/* Get the square sum of object i */
float dataset_getSquare(Dataset dataset, int i);

/* Free memory of dataset */
void dataset_free(Dataset dataset);