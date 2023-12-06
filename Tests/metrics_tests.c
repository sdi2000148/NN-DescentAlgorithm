#include <math.h>
#include "acutest.h"
#include "metrics.h"
#include "dataset.h"

static int equal(float a, float b)
{
	if (fabs(a-b) < 1.0e-8){
		return 1 ;
	}
	return 0 ;
}

void test_l2(void) {
    int dimensions = 4;
    float value;
    Dataset dataset;

    dataset_initialize(&dataset, 2, dimensions);


    for (int i = 0; i < dimensions; i++) {
        dataset_addFeature(dataset, 0, i, (float)(i + 1));
        dataset_addFeature(dataset, 1, i, (float)(i + 5));
    }
    // sqr((1-5)^2 + (2-6)^2 + (3-7)^2 + (4-8)^2) = 8

    value = l2(dataset, 0, 1);

    TEST_CHECK(equal(value, 8.0) == 1);

    dataset_free(dataset);

}

TEST_LIST = {
    {"l2", test_l2},
    {NULL, NULL} // τερματίζουμε τη λίστα με NULL
};