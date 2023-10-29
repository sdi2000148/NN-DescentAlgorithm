#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <math.h>
#include "avl.h"

struct item{
    int index ;
    double value ;
};


struct heap{
	int count ;
	int capacity ;
	struct item *array ;
	//int *indexes;
	Avl indexes_tree ;
};


// return 1 on success, 0 otherwise
int insert_index(int *indexes, int index, int k)
{
	int bucket = index % k ;
	if (indexes[bucket] == -1){
		indexes[bucket] = index ;
		return 1 ;
	}
	for (int i=bucket+1 ; i<k ; i++){
		if (indexes[i] == -1){
			indexes[i] = index ;
			return 1 ;
		}
	}
	for (int i=0 ; i<bucket ; i++){
		if (indexes[i] == -1){
			indexes[i] = index ;
			return 1 ;
		}
	}
	return 0 ; 
}


// return 1 on success, 0 otherwise
int update_index(int *indexes, int new, int old, int k)
{
	int bucket = old % k ;
	if (indexes[bucket] == old){
		indexes[bucket] = new ;
		return 1 ;
	}
	for (int i=bucket+1 ; i<k ; i++){
		if (indexes[i] == old){
			indexes[i] = new ;
			return 1 ;
		}
	}
	for (int i=0 ; i<bucket ; i++){
		if (indexes[i] == old){
			indexes[i] = new ;
			return 1 ;
		}
	}
	return 0 ; 
}


// return 1 on success, 0 otherwise
int search_index(int *indexes, int index, int k)
{
	int bucket = index % k ;
	if (indexes[bucket] == index){
		return 1 ;
	}
	for (int i=bucket+1 ; i<k ; i++){
		if (indexes[i] == index){
			return 1 ;
		}
	}
	for (int i=0 ; i<bucket ; i++){
		if (indexes[i] == index){
			return 1 ;
		}
	}
	return 0 ; 
}


// return 1 when the two floating point numbers are equal, 0 otherwise
int equal(double a, double b)
{
	if (fabs(a-b) < 1.0e-8){
		return 1 ;
	}
	return 0 ;
}


void heap_initialize(Heap *hp, int k)
{
	(*hp) = malloc(sizeof(struct heap)) ;
	(*hp)->array = malloc((k+1) * sizeof(struct item)) ; 
	//(*hp)->indexes = malloc(k * sizeof(int)) ;
	//for (int i=0 ; i<k ; i++){
	//	(*hp)->indexes[i] = -1 ;
	//}
	avl_initialize(&((*hp)->indexes_tree)) ;
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


// return 1 on success, 0 otherwise
int heap_insert(Heap hp, int index, double value)
{
	int child, parent ;

	if (heap_full(hp)){
		return 0 ;
	}

	if (heap_empty(hp)){
		hp->count++ ;
		hp->array[hp->count].index = index;
		hp->array[hp->count].value = value;
		return 1 ;
	}

	hp->count++ ;
	child = hp->count ;
	parent = child/2 ;
	while (parent != 0){ 		 // haven't reached the root of the heap tree 
		if (value > hp->array[parent].value && equal(value, hp->array[parent].value) == 0){
			hp->array[child].value = hp->array[parent].value ;
			hp->array[child].index = hp->array[parent].index ;
			child = parent ;
			parent = parent/2 ;
		}
		else{
			hp->array[child].value = value ;
			hp->array[child].index = index ;
			return 1 ;
		}
	}
	hp->array[child].value = value ;  // reached the root
	hp->array[child].index = index ;
	return 1 ;
}


// return 1 on success, 0 otherwise
int heap_replace(Heap hp, int index, double value)
{
	int current, child ;

	if (hp->array[1].value < value || equal(value, hp->array[1].value) == 1){
		return 0 ;
	}

	current = 1 ;
	child = current*2 ;
	while (child <= hp->count){
		if (child < hp->count){
			if (hp->array[child+1].value > hp->array[child].value  && equal(hp->array[child+1].value, hp->array[child].value) == 0){   // check which sibling is bigger
				child++ ;
			}
		}
		if (value > hp->array[child].value || equal(value, hp->array[child].value) == 1){
			hp->array[current].index = index ;
			hp->array[current].value = value ;
			return 1 ;
		}
		else{
			hp->array[current].index = hp->array[child].index ;
			hp->array[current].value = hp->array[child].value ;
			current = child ;
			child = child*2 ;
		}
	}
	hp->array[current].index = index ;         // reached leaf
	hp->array[current].value = value ;
	return 1 ;
}


// return 1 on change, 0 otherwise
// replaced == -1, when no replacement took place
int heap_update(Heap hp, int index, double value, int *replaced)
{
	int max = hp->array[1].index ; 
	*replaced = -1;

	//if (search_index(hp->indexes, index, hp->capacity) == 1){
	//	return 0 ;
	//}

	if (avl_search(hp->indexes_tree, index) == 1){
		return 0 ;
	}

	if (heap_insert(hp, index, value) == 1){
		//insert_index(hp->indexes, index, hp->capacity) ;
		avl_insert(hp->indexes_tree, index) ;
		return 1 ;
	}
	else if (heap_replace(hp, index, value) == 1){
		//update_index(hp->indexes, index, max, hp->capacity) ;
		avl_remove(hp->indexes_tree, max) ;
		avl_insert(hp->indexes_tree, index) ;
		*replaced = max;
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
	//free(hp->indexes) ;
	avl_free(hp->indexes_tree) ;
	free(hp) ;
}


int heap_getCapacity(Heap hp)
{
	return hp->capacity ;
}


int heap_getCount(Heap hp)
{
	return hp->count;
}


int heap_getIndex(Heap hp, int i)
{
	i++;
	if (i < 1 || i > hp->count){
		return -1;
	}
	return hp->array[i].index;
}


double heap_getValue(Heap hp, int i)
{
	i++;
	if (i < 1 || i > hp->count){
		return -1.0;
	}
	return hp->array[i].value;
}


int heap_search(Heap hp, int index)
{
	//return search_index(hp->indexes, index, hp->capacity);
	return avl_search(hp->indexes_tree, index);
}




