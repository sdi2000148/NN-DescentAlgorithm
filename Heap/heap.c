#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <math.h>


struct item{
    int index ;
    double value ;
};


struct heap{
	int count ;
	int capacity ;
	struct item *array ;
};


int equal(double a, double b)
{
	if (fabs(a-b) < 1.0e-8){
		return 1 ;
	}
	else{
		return 0 ;
	}
}


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

	if (hp->array[1].value < value || equal(value, hp->array[1].value) == 1){
		return 1 ;
	}

	current = 1 ;
	child = current*2 ;
	while (child <= hp->count){
		if (child < hp->count){
			if (hp->array[child+1].value > hp->array[child].value){
				child++ ;
			}
		}
		if (value > hp->array[child].value || equal(value, hp->array[child].value) == 1){
			hp->array[current].index = index ;
			hp->array[current].value = value ;
			return 0 ;
		}
		else if (value < hp->array[child].value){
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
	for (int i=1 ; i <= hp->count ; i++){
		if (equal(value, hp->array[i].value) == 1 && index == hp->array[i].index){
			return 0 ;
		}
	}

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


void heap_free_all(Heap *heaps, int n)
{
	for (int i=0 ; i<n ; i++){
		heap_free(heaps[i]) ;
	}
	free(heaps);
}


void swap(int *a , int *b)
{
    int help = *a ;
    *a = *b ;
    *b = help ;
    return ; 
}


void quick_sort_body(int *array , int up , int down)
{
    int start , end; ;
    start= up ;
    end= down ;
    while (up<down){
        while (array[down]>=array[up] && up<down){
            down-- ;
        }
        if (up!=down){
            swap(&array[up],&array[down]) ;
            up++ ;
        }
        while (array[up]<=array[down] && up<down){
            up++ ;
        }
        if (up!=down){
            swap(&array[up],&array[down]) ;
            down-- ;
        }
    }
    if (start<up-1){
        quick_sort_body(array,start,up-1) ;
    }
    if (end>down+1){
        quick_sort_body(array,down+1,end) ;
    }
    return ;
}

void quick_sort(int size , int *array)
{
    quick_sort_body(array,0,size-1) ;
    return ;
}


int *heap_getIndexes(Heap hp)
{
	int *indexes = malloc(hp->count * (sizeof(int))) ;
	
	for (int i=1 ; i<=hp->count ; i++){
		indexes[i-1] = hp->array[i].index ;
	}
	quick_sort(hp->count, indexes) ;
	return indexes;
}


int heap_getCapacity(Heap hp)
{
	return hp->capacity ;
}





