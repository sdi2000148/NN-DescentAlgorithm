#include "acutest.h"
#include "metrics.h"
#include "common_types.h"

void test_l2(void) {
    int dimensions = 4;
    Pointer *x = malloc(dimensions * sizeof(Pointer)), *y = malloc(dimensions * sizeof(Pointer));
    double *array1, *array2;
    array1 = malloc(dimensions * sizeof(double));
    array2 = malloc(dimensions * sizeof(double));


    for (int i = 0; i < dimensions; i++) {
        array1[i] = (double) (i + 1);
        array2[i] = (double) (i + 5);
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