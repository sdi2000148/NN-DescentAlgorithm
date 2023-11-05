#include "heap.h"
#include "brute_force.h"
#include "metrics.h"
#include "services.h"
#include "dataset.h"



/* Given the actual and the predicted solution, the number of objects N and the parameter k, calculate the recall of the 
predicted solution compared to the actual solution */
double recall(int **actual, int **predicted,  int N, int k);

/* Given a filename (or path) containting the solution of a K-NN graph in for #object: #neighbour_1, #neighbour_2, ... 
#neighbour_k, in every line, with lines equal to N, the parameter k, calculate the recall of the predicted solution compared 
to the actual solution */
double recall_file(char *filename, int **predicted, int N, int k);