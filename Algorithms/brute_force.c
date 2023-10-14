#include <stdio.h>
#include "brutal.h"
#include "PriorityQueue.h"


int brute_force(Dataset dataset, int k, Metric metric)
{
    int count;

    for (int i=0 ; i < dataset->numberOfObjects ; i++){
        
        Initialize(&dataset->objects[i]->priorityQueue, k);
        count = 0;
        for (int j=0 ; j < dataset->numberOfObjects ; j++){
            if (j == i) continue;
            if (count < k) {
                count++;
                Insert(dataset->objects[i]->priorityQueue, j, metric(dataset->objects[i]->features, dataset->objects[j]->features, dataset->dimensions));
            }
            else {
                Update(dataset->objects[i]->priorityQueue, j, metric(dataset->objects[i]->features, dataset->objects[j]->features, dataset->dimensions));
            }
        }
    }
    return 0;
}
