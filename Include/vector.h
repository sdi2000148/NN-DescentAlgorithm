#include "dataset.h"

float *hyperplane_vector_init(Dataset dataset, int index1, int index2);

float *hyperplane_midpoint_init(Dataset dataset, int index1, int index2);

float inner_product(float *vector1, float *vector2, int dimensions, float accumulator);