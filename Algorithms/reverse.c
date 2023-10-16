#include <stdio.h>
#include <stdlib.h>
#include "reverse.h"
#include "list.h"

int binary_search(int value , int size , int *array)
{
    int start , end , medium ;
    start= 0 ;
    end= size - 1 ;
    medium= (start+end)/2 ;
    while (start<=end){
        if (value<array[medium]){
            end= medium - 1 ;
        }
        else if (value > array[medium]){
            start= medium + 1 ;
        }
        else{
            return 1 ;
        }
        medium= (start+end)/2 ;
    }
    return 0 ;
}

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

            /*if(binary_search(i, heap_getCapacity(heaps[j]), indices) == 1) {
                if (binary_search(j, heap_getCapacity(heaps[j]), current_indices) == 0){
                    list_insert(result[i], j);
                }
            } */

            if (seq_search(i, heap_getCapacity(heaps[j]), indices) == 1){
                if (seq_search(j, heap_getCapacity(heaps[j]), current_indices) == 0){
                    list_insert(result[i], j);
                }
            }

            free(indices);   
        }
        free(current_indices);
    }
    return result;
}


