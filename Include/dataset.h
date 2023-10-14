typedef struct object* Object;
typedef struct dataset* Dataset;
typedef double (*Metric)(int *x, int *y, int d);


Dataset dataset_create(int dimensions, int numberOfObjects);
void nng_initialization(Dataset dataset, int k, Metric metric);
void dataset_print(Dataset dataset);
void dataset_free(Dataset dataset);

