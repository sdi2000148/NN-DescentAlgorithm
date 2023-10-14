#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


struct item{
    int index ;
    double value ;
};


struct heap{
	int count ;
	int capacity ;
	struct item *array ;
};



void heap_initialize(Heap *hp, int k)
{
	(*hp) = malloc(sizeof(struct heap)) ;
	(*hp)->array = malloc((k+1) * sizeof(struct item)) ; 
	(*hp)->count = 0 ;
	(*hp)->capacity = k ;
	return ;
}


int heap_full(Heap hp)
{
	return (hp->count == hp->capacity) ;
}


int heap_empty(Heap hp)
{
	return (hp->count == 0) ;
}


// return 0 on success, 1 otherwise
int heap_insert(Heap hp, int index, double value)
{
	int child, parent ;

	if (heap_full(hp)){
		return 1 ;
	}

	if (heap_empty(hp)){
		hp->count++ ;
		hp->array[hp->count].index = index;
		hp->array[hp->count].value = value;
		return 0 ;
	}

	hp->count++ ;
	child = hp->count ;
	parent = child/2 ;
	while (parent != 0){ 		 // haven't reached the root of the heap tree 
		if (value <= hp->array[parent].value){
			hp->array[child].value = value ;
			hp->array[child].index = index ;
			return 0 ;
		}
		else{
			hp->array[child].value = hp->array[parent].value ;
			hp->array[child].index = hp->array[parent].index ;
			child = parent ;
			parent = parent/2 ;
		}
	}
	hp->array[child].value = value ; // reached the root
	hp->array[child].index = index ;
	return 0 ;
}


// return 0 on success, 1 otherwise
int heap_replace(Heap hp, int index, double value)
{
	int current, child ;

	if (hp->array[1].value < value){
		return 1 ;
	}

	current = 1 ;
	child = current*2 ;
	while (child <= hp->count){
		if (hp->array[child+1].value > hp->array[child].value){
			child++ ;
		}
		if (value >= hp->array[child].value){
			hp->array[current].index = index ;
			hp->array[current].value = value ;
			return 0 ;
		}
		else{
			hp->array[current].index = hp->array[child].index ;
			hp->array[current].value = hp->array[child].value ;
			current = child ;
			child = child*2 ;
		}
	}
	hp->array[current].index = index ;
	hp->array[current].value = value ;
	return 0 ;
}


// return return 1 on change, or 0 otherwise
int heap_update(Heap hp, int index, double value)
{
	if (heap_insert(hp, index, value) == 0){
		return 1 ;
	}
	else if (heap_replace(hp, index, value) == 0){
		return 1 ;
	}
	else{
		return 0 ;
	}
}


void heap_print(Heap hp)
{
	for (int i=1 ; i<=(hp->count) ; i++){
        if (i == hp->count){
			printf("(%d, %f)\n",hp->array[i].index, hp->array[i].value) ;
			return ;
		}
		printf("(%d, %f) --> ",hp->array[i].index, hp->array[i].value) ;
	}
}


void heap_free(Heap hp)
{
	free(hp->array) ;
	free(hp) ;
}




