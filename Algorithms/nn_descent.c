#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "list.h"
#include "avl.h"
#include "dataset.h"
#include "services.h"
#include "nng_initialization.h"
#include "nn_descent.h"

Heap *nn_descent(Dataset dataset, int k, Metric metric) {
    double rate;
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), c, index, temp, evaluations = 0;
    Avl *avls = malloc(objects * sizeof(Avl)), *R = malloc(objects * sizeof(Avl));
    //random αρχικοποιηση της λυσης (γραφου)
    Heap *heap = nng_initialization_random(dataset, k, metric, R);
    List *U = malloc(dataset_getNumberOfObjects(dataset) * sizeof(List));
    Listnode neighbour, n_neighbour;

    for(int i = 0; i < objects; i++)
        avl_initialize(&avls[i]);

    do {
        c = 0;
        //αποθηκευση στιγμιοτυπου του γραφου ωστε οι αλλαγες να μην επηρεάζουν 
        for (int i = 0; i < objects; i++) {
            list_initialize(&U[i]);
            for (int j = 0; j < k; j++)
                list_insert(U[i], heap_getIndex(heap[i], j)); 
            avl_copyToList(R[i], U[i]);
        }

        //για καθε γειτονα των γειτονων καθε σημειου βλεπω αμα βελτιωνει την λυση μου
        for(int i = 0; i < objects; i++) {
            neighbour = list_head(U[i]);
            while(neighbour != NULL) {
                n_neighbour = list_head(U[listnode_data(neighbour)]);
                while(n_neighbour != NULL) {
                    index = listnode_data(n_neighbour);
                    if(index == i || avl_insert(avls[i], index) == 0) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    evaluations++;
                    c += nn_update(heap, i, index, metric(dataset_getFeatures(dataset, i), dataset_getFeatures(dataset, index), dimensions), R);
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }

        for (int i = 0; i < objects; i++) 
            list_free(U[i]);
        
        printf("%d\n", c);

    } while(c); //σταματαω οταν δεν εχω κανει καμια αλλαγη στην λυση μου 

    avl_free_all(R, objects);
    avl_free_all(avls, objects);

    free(U);

    temp = objects * (objects-1);
    rate = (double)(evaluations) / ((double)temp / (double)2);
    printf("nn descent scan-rate: %f\n", rate);
    
    return heap;
}


Heap *nn_descentBetter(Dataset dataset, int k, Metric metric) {
    double met, rate;
    int objects = dataset_getNumberOfObjects(dataset), dimensions = dataset_getDimensions(dataset), c, index1, index2, temp, evaluations = 0;
    Avl *avls = malloc(objects * sizeof(Avl)), *R = malloc(objects * sizeof(Avl));
    //random αρχικοποιηση της λυσης (γραφου)
    Heap *heap = nng_initialization_random(dataset, k, metric, R);
    List *U = malloc(objects * sizeof(List));
    Listnode neighbour, n_neighbour;

    for(int i = 0; i < objects; i++) 
        avl_initialize(&avls[i]);

    do {
        c = 0;
        //αποθηκευση στιγμιοτυπου του γραφου ωστε οι αλλαγες να μην επηρεάζουν 
        for (int i = 0; i < objects; i++) {
            list_initialize(&U[i]);
            for (int j = 0; j < k; j++)
                list_insert(U[i], heap_getIndex(heap[i], j));
            avl_copyToList(R[i], U[i]);
            
        }

        //για καθε συνδιασμο γειτονων (α,β) καθε σημειου βλεπω αμα ο α μπορει να προστεθει στους Κ κοντινότερους του β
        //και το αντιστροφο (local join)
        for(int i = 0; i < objects; i++) {
            neighbour = list_head(U[i]);
            while(neighbour != NULL) {
                index1 = listnode_data(neighbour);
                n_neighbour = list_next(neighbour);
                while(n_neighbour != NULL) {
                    index2 = listnode_data(n_neighbour);
                   if(avl_insert(avls[index1], index2) == 0) {
                        n_neighbour = list_next(n_neighbour);
                        continue;
                    }
                    met = metric(dataset_getFeatures(dataset, index1), dataset_getFeatures(dataset, index2), dimensions);
                    evaluations++;

                    c += nn_update(heap, index1, index2, met, R);
                    c += nn_update(heap, index2, index1, met, R);

                    //καθε φορα αποθηκευω τι εχω υπολογισει ωστε να μην κανω διπλους υπολογισμους
                    avl_insert(avls[index2], index1);
                    n_neighbour = list_next(n_neighbour);
                }
                neighbour = list_next(neighbour);
            }
        }

        for (int i = 0; i < objects; i++) 
            list_free(U[i]);

        printf("%d\n", c);
    } while(c); //σταματαω οταν δεν εχω κανει καμια αλλαγη στην λυση μου 

    avl_free_all(R, objects);
    avl_free_all(avls, objects);

    free(U);

    temp = objects * (objects-1);
    rate = (double)(evaluations) / ((double)temp / (double)2);
    printf("nn descent better scan-rate: %f\n", rate);
    
    return heap;
}

