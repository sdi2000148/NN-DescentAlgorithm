#include "acutest.h"
#include "dataset.h"

void test_dataset_initialization(void)
{
    Dataset dataset;
    int objects = 10, dimensions = 5;

    dataset_initialize(&dataset, objects, dimensions);
    TEST_CHECK(dataset_getDimensions(dataset) == dimensions);
    TEST_CHECK(dataset_getNumberOfObjects(dataset) == objects);
    for (int i = 0; i < objects; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            TEST_CHECK(dataset_getFeature(dataset, i, j) == NULL);
        }
    }
    dataset_free(dataset);
}

void test_dataset_addFeature(void)
{
    Dataset dataset;
    int objects = 10, dimensions = 5, **array, value;

    array = malloc(objects * sizeof(int *));
    for (int i = 0; i < objects; i++)
    {
        array[i] = malloc(dimensions * sizeof(int));
    }

    dataset_initialize(&dataset, objects, dimensions);

    value = 1;
    for (int i = 0; i < objects; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            array[i][j] = value;
            value++;
            TEST_CHECK(dataset_addFeature(dataset, i, j, &array[i][j]) == 0);
        }
    }

    value = 1;
    for (int i = 0; i < objects; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            TEST_CHECK(*(int *)dataset_getFeature(dataset, i, j) == value);
            value++;
        }
    }

    for (int i = 0; i < objects; i++)
    {
        free(array[i]);
    }
    free(array);

    dataset_free(dataset);
}

TEST_LIST = {
    {"dataset_initialization", test_dataset_initialization},
    {"dataset_addFeature", test_dataset_addFeature},
    {NULL, NULL} // τερματίζουμε τη λίστα με NULL
};