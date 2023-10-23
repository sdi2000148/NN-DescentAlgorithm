#include <stdio.h>
#include <stdlib.h>
#include "services.h"
#include "list.h"

int seq_search(int value , int size , int *array)
{
    int i ;
    for (i=0 ; i<size ; i++){
        if (value==array[i]){
            return 1 ;
        }
    }
    return 0 ;
}


List *reverse(Heap *heaps, int numberOfObjects) {
    int *indices;
    int *current_indices;
    List *result;

    result = malloc(numberOfObjects * sizeof(List));

    for(int i = 0; i < numberOfObjects; i++) {
        list_initialize(&result[i]);
        current_indices = heap_getIndexes(heaps[i]);
        for(int j = 0; j < numberOfObjects; j++) {
            if(i == j) continue;
            indices = heap_getIndexes(heaps[j]);
            if (seq_search(i, heap_getCapacity(heaps[j]), indices) == 1){
                if (seq_search(j, heap_getCapacity(heaps[j]), current_indices) == 0){
                    list_insert(result[i], j);
                }
            }
        }
    }
    return result;
}

int nn_update(Heap *B, int v, int u, double l, List *R)
{
	int r; 
	if (heap_update(B[v], u, l, &r) == 0){
		return 0;
	}
	else{
		if (r == -1){
            list_remove(R[v], u);
			if (heap_search(B[u], v) == 0){
        		list_insert(R[u], v);
            }
		}
		else{
			list_remove(R[r], v);
			if (heap_search(B[u], v) == 0){
        		list_insert(R[u], v);
			}
            if (heap_search(B[r], v) == 1){
        		list_insert(R[v], r);
			}
		}
		return 1;
	}
}

void heap_free_all(Heap *heaps, int n)
{
	for (int i=0 ; i<n ; i++){
		heap_free(heaps[i]) ;
	}
	free(heaps);
}


void actual_solution(Heap *heaps, char *path, int N, int k) {
    FILE *fp = fopen(path, "w");
    int *act;

    // #object : #n1 #n2 #n3 

    for (int i=0 ; i<N ; i++){
        act = heap_getIndexes(heaps[i]);
        fprintf(fp, "%d:", i);
        for (int j=0 ; j<k-1; j++){
            fprintf(fp, "%d,", act[j]);
        }
        fprintf(fp, "%d\n", act[k-1]);
    }

    fclose(fp);
}