#include "acutest.h"
#include "metrics.h"
#include "common_types.h"

void test_l2(void) {
    int dimensions = 4;
    Pointer *x = malloc(dimensions * sizeof(Pointer)), *y = malloc(dimensions * sizeof(Pointer));
    float *array1, *array2;
    array1 = malloc(dimensions * sizeof(float));
    array2 = malloc(dimensions * sizeof(float));


    for (int i = 0; i < dimensions; i++) {
        array1[i] = (float) (i + 1);
        array2[i] = (float) (i + 5);
    }

    for (int i = 0; i < dimensions; i++) {
        x[i] = &array1[i];
        y[i] = &array2[i];
    }

    double value = l2(x, y, dimensions);

    TEST_CHECK(value == 8.0);

    free(x);
    free(y);
    free(array1);
    free(array2);
}

TEST_LIST = {
    {"l2", test_l2},
    {NULL, NULL} // τερματίζουμε τη λίστα με NULL
};