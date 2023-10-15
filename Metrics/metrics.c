#include <math.h>
#include <stdlib.h>

double l2(int *x, int *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = abs(x[i]- y[i]);
        result += pow(value, 2.0);
    }
    return sqrt(result);
}