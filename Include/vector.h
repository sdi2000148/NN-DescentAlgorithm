#include "dataset.h"

/* Initialization of vector of index1 and index2 of dataset's objects */
float * hyperplane_vector_init(Dataset dataset, int index1, int index2);

/* Return the midpoint of index1 and index2 of dataset's objects */
float * hyperplane_midpoint_init(Dataset dataset, int index1, int index2);

/* Return the inner product of vector1 and vector2, specified the dimensions and given an accumulator */
float inner_product(float * vector1, float * vector2, int dimensions, float accumulator);