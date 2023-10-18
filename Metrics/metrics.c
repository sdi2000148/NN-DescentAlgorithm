#include <math.h>
#include <stdlib.h>
#include "common_types.h"


double l2(Pointer *x, Pointer *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = abs(*(int*)x[i]- *(int*)y[i]);
        result += pow(value, 2.0);
    }
    return sqrt(result);
}