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


List *reverse(Heap *heap, int numberOfObjects) {
    List *R = malloc(numberOfObjects * sizeof(List));

    for (int i=0 ; i < numberOfObjects ; i++){
        list_initialize(&R[i]);
    }

    for(int i=0; i < numberOfObjects; i++) {
        for(int j=i+1; j < numberOfObjects; j++) {   // start from i+1
            if (heap_search(heap[j], i) == 1){
                if (heap_search(heap[i], j) == 0){
                    list_insert(R[i], j);
                }
            }
            if (heap_search(heap[i], j) == 1){
                if (heap_search(heap[j], i) == 0){
                    list_insert(R[j], i);
                }
            }
        }
    }
    return R;
}

int nn_update(Heap *B, int v, int u, double l, Avl *R)
{
	int r;
    
	if (heap_update(B[v], u, l, &r) == 0){
		return 0;
	}
	else{
		if (r == -1){ // graph is not fully initialized
            // to avoid duplicates, try to remove u from the reverse neighbours of v 

			if (avl_remove(R[v], u) == 0){ // u is not reverse neighbour of v
        		avl_insert(R[u], v); 
                // add v to the reverse neighbours of u 
                // case 1: the graph looks like that: (v -> u)
            }
            // else, if the remove succeed, 
            // case 2: the graph looks like that: (v <-> u)

		}
		else{ // graph is initialized

            // to avoid duplicates, try to remove u from the reverse neighbours of v 

			if (avl_remove(R[v], u) == 0){ //try to remove u from reverse neighbours of v
        		avl_insert(R[u], v); 
                // add v to the reverse neighbours of u
                // case 1: the graph looks like that: (v -> u) 
            }

            // else, if the remove succeed, 
            // case 2: the graph looks like that: (v <-> u)
            
            if (avl_remove(R[r], v) == 0){ // try to remove v for the reverse neighbours of r
        		avl_insert(R[v], r); 
                // add r to the reverse neighbours of v
                // case 1: the graph look like that: (r -> v)
			}

            // else, if the remove succeed, 
            // case 2: the graph looks like that: (r and v not connected at all)

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

void avl_free_all(Avl *avls, int n) {
    for(int i = 0; i < n; i++) 
        avl_free(avls[i]);
    free(avls);
}

void neighbours_free_all(int **neighbours, int n) {
    for(int i = 0; i < n; i++)
        free(neighbours[i]);
    free(neighbours);
}


void save_solution(int **neighbours, char *path, int N, int k) {
    FILE *fp = fopen(path, "w");

    // #object : #n1 #n2 #n3 

    for (int i=0 ; i<N ; i++){
        fprintf(fp, "%d:", i);
        for (int j=0 ; j<k-1; j++){
            fprintf(fp, "%d,", neighbours[i][j]);
        }
        fprintf(fp, "%d\n", neighbours[i][k-1]);
    }

    fclose(fp);
}


int **getNeighbours(Heap *heaps, int N, int k) {
    int **neighbours = malloc(N * sizeof(int *));

    for (int i=0 ; i<N ; i++){
        if (heap_getCount(heaps[i]) < k){
            return NULL;
        } 
        neighbours[i] = malloc(k * sizeof(int));
        for (int j=k-1 ; j>=0 ; j--){
            neighbours[i][j] = heap_getMaxIndex(heaps[i]);
            heap_remove(heaps[i]);
        }
    }

    return neighbours;

}