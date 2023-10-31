#include <math.h>
#include <stdlib.h>
#include "common_types.h"


double l2(Pointer *x, Pointer *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = (double)(*(float*)x[i] - *(float*)y[i]);
        value = value*value;
        result += value;
    }
    return sqrt(result);
}

double manhattan(Pointer *x, Pointer *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = (double)(*(float*)x[i] - *(float*)y[i]);
        result += fabs(value);
    }
    return result;
}

double l2_double(Pointer *x, Pointer *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = fabs(*(double*)x[i]- *(double*)y[i]);
        result += pow(value, 2.0);
    }
    return sqrt(result);
}