#include <stdio.h>
#include <stdlib.h>
#include "services.h"
#include "list.h"
#include "avl.h"

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


void reverse(List *U, List *R, int numberOfObjects) {
    Listnode neighbour;
    int index;

    for (int i=0 ; i < numberOfObjects ; i++){
        list_initialize(&R[i]);
    }

    for(int i = 0; i < numberOfObjects; i++) {
        neighbour = list_head(U[i]);
        while(neighbour != NULL) {
            index = listnode_data(neighbour);
            list_insert(R[index], i);

            neighbour = list_next(neighbour);
        }
    }

    return;
}


void strict_reverse(List *U, List *R, int numberOfObjects, Heap *heaps) {
    Listnode neighbour;
    int index;

    for (int i=0 ; i < numberOfObjects ; i++){
        list_initialize(&R[i]);
    }

    for(int i = 0; i < numberOfObjects; i++) {
        neighbour = list_head(U[i]);
        while(neighbour != NULL) {
            index = listnode_data(neighbour);
            if(heap_search(heaps[index], i) == 0)
                list_insert(R[index], i);

            neighbour = list_next(neighbour);
        }
    }



    return;
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