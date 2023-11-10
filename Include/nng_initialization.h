#include "dataset.h"
#include "heap.h"
#include "list.h"
#include "avl.h"


/* Initialization of random K-NN graph given the dataset, the k and the metric, as well as initialization 
of R and avls avl tree arrays with sizes equal to the number of objects in the dataset. R contains all the 
reverse neighbours for every object, and avls contains all the other objects that every object was compared
to. */
Heap* nng_initialization_random(Dataset dataset, int k, Metric metric);