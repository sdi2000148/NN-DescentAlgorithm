#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "avl.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#include "knn_search.h"
#include <math.h>
#include "heap.h"


// return 1 when the two floating point numbers are equal, 0 otherwise
static int equal(double a, double b)
{
	if (fabs(a-b) < 1.0e-12){
		return 1 ;
	}
	return 0 ;
}


// get best untried candidate node in the pool
// return -1 when pool is empty or when there are no untried candidate nodes left
static int get_candidate(Heap pool, Avl computed, int k)
{
    int *indexes = malloc(k * sizeof(int)), pool_len = heap_getCount(pool), candidate = -1;
    double *values = malloc(k * sizeof(double));

    if (pool_len == 0){
        return -1;
    }

    for (int i=pool_len-1 ; i>=0 ; i--){     // get nodes in descending order of similarity 
        values[i] = heap_getMaxValue(pool);
        indexes[i] = heap_getMaxIndex(pool);
        heap_remove(pool);
    }

    for (int i=0 ; i < pool_len ; i++){      // rebuild heap  
        heap_update(pool, indexes[i], values[i]);
    }

    for (int i=0 ; i < pool_len ; i++){
        if (avl_search(computed, indexes[i]) == 0){    // found the best untried node
            candidate = indexes[i];
            avl_insert(computed, candidate);
            break;
        }
    }

    free(indexes);
    free(values);

    return candidate;
}


int *search_knn(Dataset dataset, int **graph, float *object, int k, Metric_search metric)
{
    Heap pool;
    Avl computed;
    int *indexes = malloc(k * sizeof(int));
    int current, pool_len, neighbor, self = -1;
    double val;

    heap_initialize(&pool, k);
    avl_initialize(&computed);

    srand(time(NULL));
    current = rand() % dataset_getNumberOfObjects(dataset);    // randomly chosen candidate node
    val = metric(dataset, current, object);

    if (equal(val, 0.0) == 1){
        self = current;
    }
    else{
        heap_update(pool, current, val);
    }

    while (1){
        if (self == -1){
            current = get_candidate(pool, computed, k);  
        }
        else{
            current = self;
            self = -1;
        }


        if (current == -1){
            break;
        }

        for (int i=0 ; i < k ; i++){        // for every neighbor of the current candidate node
            neighbor = graph[current][i]; 
            val = metric(dataset, neighbor ,object);
            if (equal(val, 0.0) == 1){
                self = neighbor;
                continue;
            }
            heap_update(pool, neighbor, val);
        }

    }

    pool_len = heap_getCount(pool);
    for (int i=pool_len-1 ; i>=0 ; i--){
        indexes[i] = heap_getMaxIndex(pool);
        heap_remove(pool);
    }

    heap_free(pool);
    avl_free(computed);

    if (pool_len < k){
        free(indexes);
        return NULL;
    }

    return indexes;
}


int *search_knn_brute_force(Dataset dataset, float *object, int k, Metric_search metric)
{
    Heap heap;
    int heap_len;
    int *indexes = malloc(k * sizeof(int));
    double val;

    heap_initialize(&heap, k);

    for (int i=0 ; i < dataset_getNumberOfObjects(dataset) ; i++){
        val = metric(dataset, i, object);
        if (equal(val, 0.0) == 1){
            continue;
        }
        heap_update(heap, i, val);
    }
    
    heap_len = heap_getCount(heap);
    for (int i=heap_len-1 ; i>=0 ; i--){
        indexes[i] = heap_getMaxIndex(heap);
        heap_remove(heap);
    }

    heap_free(heap);

    return indexes;
}







