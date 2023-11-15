#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

int **nn_descent(Dataset dataset, int k, Metric metric) {
    double val;
    long double rate;
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), c, index, index1, index2, **neighbours, flag,
    sampling = (int)(0.4 *(float)k), count1, count2;
    unsigned int evaluations = 0, temp;
    Heap *heaps = nng_initialization_random(dataset, k, metric), *new = malloc(objects * sizeof(Heap)), *old = malloc(objects * sizeof(Heap));
    float d = 0.001;

    do {
        c = 0;

        for(int i = 0; i < objects; i++) {
            heap_initialize(&old[i], k + sampling);
            heap_initialize(&new[i], 2*sampling);
        }
    

        for(int i = 0; i < objects; i++) {
            for(int j = 0; j < k; j++) {
                index = heap_getIndex(heaps[i], j);
                flag = heap_getFlag(heaps[i], j);
                if(flag == 0) {
                    heap_update(old[i], index, -1.0);
                    heap_update(old[index], i, (double)rand());
                }
                else { // sampling
                    heap_update(new[i], index, (double)rand());
                    heap_setFlag(heaps[i], j);
                    heap_update(new[index], i, (double)rand());
                }
            }
        }

        for(int i = 0; i < objects; i++) {
            count1 = 0;
            while((index1 = heap_getIndex(new[i], count1)) != -1) {
                count2 = count1 + 1;
                while((index2 = heap_getIndex(new[i], count2)) != -1) {
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    evaluations++;
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    count2++;
                }
                count2 = 0;
                while((index2 = heap_getIndex(old[i], count2)) != -1) {
                    val = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    evaluations++;
                    c += heap_update(heaps[index1], index2, val);
                    c += heap_update(heaps[index2], index1, val);
                    count2++;
                }
                count1++;
            }
        }

        for(int i = 0; i < objects; i++) {
            heap_free(new[i]);
            heap_free(old[i]);
        }

        printf("%d\n", c);
    } while(c > (int)(d * (float)(objects * k)));

    temp = (unsigned int)objects * ((unsigned int)objects-1) / 2;
    rate = (long double)(evaluations) / (long double)temp; // scan rate
    printf("nn descent scan-rate: %Lf\n", rate);

    neighbours = getNeighbours(heaps, objects, k);

    heap_free_all(heaps, objects);
    free(new);
    free(old);

    return neighbours;
}

