#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "avl.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"
#include "knn_search.h"

int *search_knn(Dataset dataset, Heap *heap, Pointer *object, int k, Metric metric)
{
    Heap pool;
    Avl computed;
    int current, checked = 0, replaced, pool_len, neighbor;
    int *indexes = malloc(k * sizeof(int));
    double *values = malloc(k * sizeof(double));

    srand(time(NULL));
    current = rand() % dataset_getNumberOfObjects(dataset);  // randomly chosen candidate node

    heap_initialize(&pool, k);
    avl_initialize(&computed);

    heap_update(pool, current, metric(dataset_getFeatures(dataset, current), object, dataset_getDimensions(dataset)), &replaced);

    while (checked == 0){
        checked = 1;
        pool_len = heap_getCount(pool);

        for (int i=pool_len-1 ; i>=0 ; i--){
            values[i] = heap_getMaxValue(pool);
            indexes[i] = heap_getMaxIndex(pool);
            heap_remove(pool);
        }

        for (int i=0 ; i < pool_len ; i++){
            heap_update(pool, indexes[i], values[i], &replaced);
        }

        for (int i=0 ; i < pool_len; i++){
            current = indexes[i];

            if (avl_search(computed, current) == 1){
                continue;
            }

            checked = 0;
            avl_insert(computed, current);
            
            for (int j=0 ; j < heap_getCount(heap[current]) ; j++){   // for every neighbor of the current candidate node
                neighbor = heap_getIndex(heap[current], j);
                heap_update(pool, neighbor, metric(dataset_getFeatures(dataset, neighbor), object, dataset_getDimensions(dataset)), &replaced);
            }
        }
    }

    pool_len = heap_getCount(pool);
    for (int i=pool_len-1 ; i>=0 ; i--){
        indexes[i] = heap_getMaxIndex(pool);
        heap_remove(pool);
    }

    heap_free(pool);
    avl_free(computed);
    free(values);

    return indexes;
}



int *search_knn_brute_force(Dataset dataset, Pointer *object, int k, Metric metric)
{
    Heap heap;
    int replaced, heap_len;
    int *indexes = malloc(k * sizeof(int));

    heap_initialize(&heap, k);

    for (int i=0 ; i < dataset_getNumberOfObjects(dataset) ; i++){
        heap_update(heap, i, metric(dataset_getFeatures(dataset, i), object, dataset_getDimensions(dataset)), &replaced);
    }
    
    heap_len = heap_getCount(heap);
    for (int i=heap_len-1 ; i>=0 ; i--){
        indexes[i] = heap_getMaxIndex(heap);
        heap_remove(heap);
    }

    heap_free(heap);

    return indexes;
}





