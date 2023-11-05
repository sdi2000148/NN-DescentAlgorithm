#include "heap.h"
#include "brute_force.h"
#include "metrics.h"
#include "services.h"
#include "dataset.h"


/* Given a filename (or path) containting the solution of a K-NN graph in for #object: #neighbour_1, #neighbour_2, ... 
#neighbour_k, in every line, with lines equal to the number of objects of the dataset, the parameter k, the dataset 
and the desired metric, calculate the recall of the predicted solution compared to the actual solution */
double recall(char *filename, int **predicted, int k, Dataset dataset, Metric metric);