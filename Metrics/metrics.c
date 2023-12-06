#include <math.h>
#include <stdlib.h>
#include "metrics.h"
#include "dataset.h"


float l2(Dataset dataset, int x, int y) {
    float result = 0.0, x_value, y_value, value;
    int dimennsions = dataset_getDimensions(dataset);
    for(int i = 0; i < dimennsions; i++) {
        x_value = dataset_getFeature(dataset, x, i);
        y_value = dataset_getFeature(dataset, y, i);
        value = x_value - y_value;
        value = value*value;
        result += value;
    }
    return sqrt(result);
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


