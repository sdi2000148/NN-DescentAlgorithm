#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

typedef struct PQ_node* PriorityQueueNode;

struct PQ{
	int count ;
	int max ;
	PriorityQueueNode array;
};

struct PQ_node {
    int index;
    double value;
};


void Initialize(PriorityQueue * pq, int k)
{
	(*pq) = malloc(sizeof(struct PQ)) ;
	(*pq)->array = malloc(sizeof(struct PQ_node) * (k+1));
	(*pq)->count = 0 ;
	(*pq)->max = k ;
	return ;
}

void Free(PriorityQueue pq)
{
	free(pq->array) ;
	free(pq) ;
}



int Empty(PriorityQueue pq)
{
	return (pq->count == 0) ;
}


void Insert(PriorityQueue pq , int index, double value)
{

	if (pq->count == pq->max){
        printf("Heap is full.\n") ;
        return ;
    }

	if (Empty(pq)){
		pq->count++ ;
		pq->array[pq->count].index = index;
		pq->array[pq->count].value = value;
		return ;
	}

	pq->count++ ;
	int Childloc , Parentloc ;
	Childloc = pq->count ;
	Parentloc = Childloc/2 ;
	while (Parentloc!=0){ 	// Haven't reached the root of the heap tree 
		if (value <= pq->array[Parentloc].value){
			pq->array[Childloc].value = value ;
			pq->array[Childloc].index = index ;
			return ;
		}
		else{
			pq->array[Childloc].value = pq->array[Parentloc].value ;
			pq->array[Childloc].index = pq->array[Parentloc].index ;
			Childloc = Parentloc ;
			Parentloc = Parentloc/2 ;
		}
	}
	pq->array[Childloc].value = value ; // same as : pq->array[1] = data ; | Reached the root
	pq->array[Childloc].index = index ;
	return ;
}





int Update(PriorityQueue pq, int index, double value)
{
	if (pq->array[1].value < value){
		return 0 ;
	}

	//int ItemToInsert = pq->array[pq->count] ;
	int IndexToInsert = index ;
	int ValuetoInsert = value ;

	int Currentloc , Childloc ;
	Currentloc = 1 ;
	Childloc = Currentloc*2 ;
	while (Childloc <= pq->count){
		if (pq->array[Childloc+1].value > pq->array[Childloc].value){
			Childloc++ ;
		}
		if (ValuetoInsert >= pq->array[Childloc].value){
			pq->array[Currentloc].index = IndexToInsert ;
			pq->array[Currentloc].value = ValuetoInsert ;
			return 1 ;
		}
		else{
			pq->array[Currentloc].index = pq->array[Childloc].index ;
			pq->array[Currentloc].value = pq->array[Childloc].value ;
			Currentloc = Childloc ;
			Childloc = Childloc*2 ;
		}
	}
	pq->array[Currentloc].index = IndexToInsert ;
	pq->array[Currentloc].value = ValuetoInsert ;
	return 1 ;
}



void Print_PQ(PriorityQueue pq)
{
	for (int i=1 ; i<=(pq->count) ; i++){
        if (i == pq->count){
			printf("(%d, %f)\n",pq->array[i].index, pq->array[i].value) ;
			return ;
		}
		printf("(%d, %f) --> ",pq->array[i].index, pq->array[i].value) ;
	}
}






