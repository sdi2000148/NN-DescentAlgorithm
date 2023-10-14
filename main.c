#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "brutal.h"

double l2(int *x, int *y, int d) {
    double result = 0.0, value;
    for(int i = 0; i < d; i++) {
        value = abs(x[i]- y[i]);
        result += pow(value, 2.0);
    }
    return sqrt(result);
}



int main(void) {
    Dataset dataset = dataset_create(2, 5);
    brute_force(dataset, 3, l2);
    //nng_initialization(dataset, 3, l2);
    dataset_print(dataset);
    dataset_free(dataset);

    

    return 0;
}