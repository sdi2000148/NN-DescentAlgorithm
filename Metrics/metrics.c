#include <math.h>
#include <stdlib.h>
#include "metrics.h"
#include "dataset.h"

float l2(Dataset dataset, int x, int y) {
    float x_value, y_value, x_square, y_square, value = 0.0;
    int dimennsions = dataset_getDimensions(dataset);

    x_square = dataset_getSquare(dataset, x);
    y_square = dataset_getSquare(dataset, y);

    for(int i = 0; i < dimennsions; i++) {
        x_value = dataset_getFeature(dataset, x, i);
        y_value = dataset_getFeature(dataset, y, i);
        value += x_value * y_value;
    }

    return x_square + y_square - 2 * value;
}


float l2_search(Dataset dataset, int x, float *y) {
    float result = 0.0, x_value, y_value, value;
    int dimennsions = dataset_getDimensions(dataset);
    for(int i = 0; i < dimennsions; i++) {
        x_value = dataset_getFeature(dataset, x, i);
        y_value = y[i];
        value = x_value - y_value;
        value = value*value;
        result += value;
    }
    return sqrt(result);
}


