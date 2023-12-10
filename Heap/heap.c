#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <math.h>
#include "avl.h"

struct item{
    int index ;
	int flag;
    float value ;
};


struct heap{
	int count ;
	int capacity ;
	struct item *array ;
	Avl indexes ;
};


// return 1 when the two floating point numbers are equal, 0 otherwise
static int equal(float a, float b)
{
	if (fabsf(a-b) < 1.0e-8){
		return 1 ;
	}
	return 0 ;
}


void heap_initialize(Heap *hp, int k)
{
	(*hp) = malloc(sizeof(struct heap)) ;
	(*hp)->array = malloc((k+1) * sizeof(struct item)) ; 
	(*hp)->count = 0 ;
	(*hp)->capacity = k ;
	avl_initialize(&((*hp)->indexes)) ;
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


// insert new item in heap
// return 1 on success, 0 otherwise
static int heap_insert(Heap hp, int index, float value)
{
	int child, parent ;

	if (heap_full(hp)){
		return 0 ;
	}

	if (heap_empty(hp)){
		hp->count++ ;
		hp->array[hp->count].index = index;
		hp->array[hp->count].value = value;
		hp->array[hp->count].flag = 1;
		return 1 ;
	}

	hp->count++ ;
	child = hp->count ;
	parent = child/2 ;
	while (parent != 0){ 		 // haven't reached the root of the heap tree 
		if (value > hp->array[parent].value && equal(value, hp->array[parent].value) == 0){
			hp->array[child].value = hp->array[parent].value ;
			hp->array[child].index = hp->array[parent].index ;
			hp->array[child].flag = hp->array[parent].flag ;
			child = parent ;
			parent = parent/2 ;
		}
		else{
			hp->array[child].value = value ;
			hp->array[child].index = index ;
			hp->array[child].flag = 1 ;
			return 1 ;
		}
	}
	hp->array[child].value = value ;  // reached the root
	hp->array[child].index = index ;
	hp->array[child].flag = 1 ;
	return 1 ;
}


// replace root of heap with new item
// return 1 on success, 0 otherwise
static int heap_replace(Heap hp, int index, float value)
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
			hp->array[current].flag = 1 ;
			return 1 ;
		}
		else{
			hp->array[current].index = hp->array[child].index ;
			hp->array[current].value = hp->array[child].value ;
			hp->array[current].flag = hp->array[child].flag ;
			current = child ;
			child = child*2 ;
		}
	}
	hp->array[current].index = index ;         // reached leaf
	hp->array[current].value = value ;
	hp->array[current].flag = 1 ;
	return 1 ;
}


// return removed index, otherwise return -1
int heap_remove(Heap hp)
{
	int returned_index = hp->array[1].index;
	int index = hp->array[hp->count].index;
	float value = hp->array[hp->count].value; 
	int current, child ;

	if (heap_empty(hp)){
		return -1;
	}

	hp->count--;
	avl_remove(hp->indexes, returned_index);
	
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
			hp->array[current].flag = 1 ;
			return returned_index ;
		}
		else{
			hp->array[current].index = hp->array[child].index ;
			hp->array[current].value = hp->array[child].value ;
			hp->array[current].flag = hp->array[child].flag ;
			current = child ;
			child = child*2 ;
		}
	}

	hp->array[current].index = index ;         // reached leaf
	hp->array[current].value = value ;
	hp->array[current].flag = 1 ;

	return returned_index;
}


int heap_update(Heap hp, int index, float value)
{
	int max = hp->array[1].index ; 

	if (avl_search(hp->indexes, index) == 1){
		return 0 ;
	}

	if (heap_insert(hp, index, value) == 1){
		avl_insert(hp->indexes, index) ;
		return 1 ;
	}
	else if (heap_replace(hp, index, value) == 1){
		avl_remove(hp->indexes, max) ;
		avl_insert(hp->indexes, index) ;
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
	avl_free(hp->indexes) ;
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


float heap_getValue(Heap hp, int i)
{
	i++;
	if (i < 1 || i > hp->count){
		return -1.0;
	}
	return hp->array[i].value;
}


int heap_getFlag(Heap hp, int i)
{
	i++;
	if (i < 1 || i > hp->count){
		return -1;
	}
	return hp->array[i].flag;
}


int heap_setFlag(Heap hp, int i)
{
	i++;
	if (i < 1 || i > hp->count){
		return -1;
	}
	hp->array[i].flag = 0;
	return 1;
}


int heap_getMaxIndex(Heap hp)
{
	if (heap_empty(hp)){
		return -1;
	}
	return hp->array[1].index;
}


float heap_getMaxValue(Heap hp)
{
	if (heap_empty(hp)){
		return -1.0;
	}
	return hp->array[1].value;
}


int heap_getMaxFlag(Heap hp)
{
	if (heap_empty(hp)){
		return -1;
	}
	return hp->array[1].flag;
}


int heap_search(Heap hp, int index)
{
	return avl_search(hp->indexes, index);
}




