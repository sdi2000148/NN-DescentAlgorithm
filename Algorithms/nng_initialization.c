#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "nng_initialization.h"
#include "services.h"
#include "avl.h"
#include "time.h"
#include "metrics.h"
#include "vector.h"

static int equal(float a, float b)
{
	if (fabsf(a-b) < 1.0e-8){
		return 1 ;
	}
	return 0 ;
}

Heap* nng_initialization_random(Dataset dataset, int k, Metric metric) {
    int objects = dataset_getNumberOfObjects(dataset), index, *samples, unique;
    Heap *heaps;
    float val;

    # pragma omp single copyprivate(heaps)
    heaps = malloc(objects* (sizeof(Heap)));

    samples = malloc(objects*sizeof(int));

    if (objects <= k) {
        # pragma omp single
        printf("K is bigger or equal than the given objects!\n");
        return NULL;
    }

    # pragma omp for
    for (int i = 0; i < objects; i++) {
        heap_initialize(&heaps[i], k);
    }
    
    # pragma omp for
    for (int i = 0; i < objects; i++) {
        for(int j = 0; j < objects; j++) 
            samples[j] = 0;

        samples[i] = 1;
        for(int j = 0; j < k; j++) {
            unique = 0;
            do {
                index = rand() % objects;
                if(samples[index] == 0) {
                    unique = 1;
                    samples[index] = 1;
                }
            } while(!unique); // duplicate avoidance 

            val = metric(dataset, index, i);
            heap_update(heaps[i], index, val);
        }
    }

    free(samples);
    return heaps;
}

static void rpt_split_rec(Dataset dataset, Heap *heaps, Metric metric, int *indexes, int start, int end, int threshold, int *temp, omp_lock_t *locks) {
    int point1, point2, dimensions = dataset_getDimensions(dataset), left = start, right = end, index1, index2;
    float offset, margin, *vector, *midpoint, *data, value;

    point1 = rand() % (end - start + 1) + start;

    do {
        point2 = rand() % (end - start + 1) + start;
    } while(point1 == point2);

    vector = hyperplane_vector_init(dataset, indexes[point1], indexes[point2]); // vector between the first two random points
    midpoint = hyperplane_midpoint_init(dataset, indexes[point1], indexes[point2]); // midpoint between the first two random points

    offset = inner_product(vector, midpoint, dimensions, 0.0); // offset that is used as accumulator for the margin 

    for(int i = start; i <= end; i++) {
        data = dataset_getFeatures(dataset, indexes[i]);
        margin = inner_product(vector, data, dimensions, offset); // margin that determines which side a point is on

        if(equal(margin, 0.0) == 1) {
            if(rand() % 2 == 0) {
                temp[left++] = indexes[i];
            }
            else {
                temp[right--] = indexes[i];
            }
        }
        else if(margin < 0.0) {
            temp[left++] = indexes[i];
        }
        else {
            temp[right--] = indexes[i];
        }
    }

    if(left == start || right == end) { // all points happened to be on one side only
        for(int i = start; i <= end; i++) {
            if(rand() % 2 == 0) {
                temp[left++] = indexes[i];
            }
            else {
                temp[right--] = indexes[i];
            }
        }
    }    

    left--;
    right++;

    memcpy(indexes + start, temp + start, (end - start + 1) * sizeof(int));
    if(left - start + 1 <= threshold || end - right + 1 <= threshold) { // threshold reached
        for(int i = start; i <= end; i++) {
            index1 = indexes[i];
            for(int j = i + 1; j <= end; j++) {
                index2 = indexes[j];
                value = metric(dataset, index1, index2);
                omp_set_lock(&locks[index1]);
                heap_update(heaps[index1], index2, value);
                omp_unset_lock(&locks[index1]);

                omp_set_lock(&locks[index2]);
                heap_update(heaps[index2], index1, value);
                omp_unset_lock(&locks[index2]);
            }
        }
    }
    else {
        rpt_split_rec(dataset, heaps, metric, indexes, start, left, threshold, temp, locks);
        rpt_split_rec(dataset, heaps, metric, indexes, right, end, threshold, temp, locks);
    }

    free(vector);
    free(midpoint);
}

Heap *nng_initialization_rpt(Dataset dataset, Metric metric, int k, int trees, int threshold, omp_lock_t *locks) {
    int dimensions = dataset_getDimensions(dataset), objects = dataset_getNumberOfObjects(dataset), *indexes, *temp, index1, index2, \
    left, right;
    float offset, margin, *vector, *midpoint, *data, value;
    Heap *heaps;

    # pragma omp single copyprivate(heaps)
    {
        heaps = malloc(objects* (sizeof(Heap)));
    }

    indexes = malloc(objects * sizeof(int));
    temp = malloc(objects * sizeof(int));

    # pragma omp for
    for (int i = 0; i < objects; i++) {
        heap_initialize(&heaps[i], k);
    }

    # pragma omp for
    for(int i = 0; i < trees; i++) {
        index1 = rand() % objects;

        do {
            index2 = rand() % objects; 
        } while(index1 == index2);

        vector = hyperplane_vector_init(dataset, index1, index2); // vector between the first two random points
        midpoint = hyperplane_midpoint_init(dataset, index1, index2); // midpoint between the first two random points

        offset = inner_product(vector, midpoint, dimensions, 0.0); // offset that is used as accumulator for the margin 
        left = 0;
        right = objects - 1;

        for(int j = 0; j < objects; j++) {
            data = dataset_getFeatures(dataset, j);
            margin = inner_product(vector, data, dimensions, offset); // margin that determines which side a point is on

            if(equal(margin, 0.0) == 1) {
                if(rand() % 2 == 0) {
                    indexes[left++] = j;
                }
                else {
                    indexes[right--] = j;
                }
            }
            else if(margin < 0.0) {
                indexes[left++] = j;
            }
            else {
                indexes[right--] = j;
            }
        }

        if(left == 0 || right == objects - 1) { // all points happened to be on one side only
            for(int i = 0; i <= objects - 1; i++) {
                if(rand() % 2 == 0) {
                    temp[left++] = indexes[i];
                }
                else {
                    temp[right--] = indexes[i];
                }
            }
        }    

        left--;
        right++;

        if(left + 1 <= threshold || objects - right <= threshold) { // threshold reached
            for(int i = 0; i <= objects - 1; i++) {
                index1 = indexes[i];
                for(int j = i + 1; j <= objects - 1; j++) {
                    index2 = indexes[j];
                    value = metric(dataset, index1, index2);

                    omp_set_lock(&locks[index1]);
                    heap_update(heaps[index1], index2, value);
                    omp_unset_lock(&locks[index1]);

                    omp_set_lock(&locks[index2]);
                    heap_update(heaps[index2], index1, value);
                    omp_unset_lock(&locks[index2]);
                }
            }
        }
        else {
            rpt_split_rec(dataset, heaps, metric, indexes, 0, left, threshold, temp, locks);
            rpt_split_rec(dataset, heaps, metric, indexes, right, objects - 1, threshold, temp, locks);   
        }
        free(vector);
        free(midpoint);
    }

    free(temp);
    free(indexes);

    return heaps;
}



