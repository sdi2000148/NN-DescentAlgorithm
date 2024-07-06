#include <math.h>

#include "acutest.h"

#include "dataset.h"

static int equal(float a, float b) {
  if (fabsf(a - b) < 1.0e-8) {
    return 1;
  }
  return 0;
}

void test_dataset_initialization(void) {
  Dataset dataset;
  int objects = 10, dimensions = 5;

  dataset_initialize( & dataset, objects, dimensions);

  TEST_CHECK(dataset_getDimensions(dataset) == dimensions);
  TEST_CHECK(dataset_getNumberOfObjects(dataset) == objects);

  for (int i = 0; i < objects; i++) {
    for (int j = 0; j < dimensions; j++) {
      TEST_CHECK(equal(dataset_getFeature(dataset, i, j), 0.0) == 1);
    }
  }
  dataset_free(dataset);
}

void test_dataset_addFeature(void) {
  Dataset dataset;
  int objects = 10, dimensions = 5;
  float value = 1.0;

  dataset_initialize( & dataset, objects, dimensions);

  for (int i = 0; i < objects; i++) {
    for (int j = 0; j < dimensions; j++) {
      TEST_CHECK(dataset_addFeature(dataset, i, j, value) == 0);
    }
  }

  for (int i = 0; i < objects; i++) {
    for (int j = 0; j < dimensions; j++) {
      TEST_CHECK(equal(dataset_getFeature(dataset, i, j), value) == 1);
    }
  }

  dataset_free(dataset);
}

TEST_LIST = {
  {
    "dataset_initialization",
    test_dataset_initialization
  },
  {
    "dataset_addFeature",
    test_dataset_addFeature
  },
  {
    NULL,
    NULL
  }
};