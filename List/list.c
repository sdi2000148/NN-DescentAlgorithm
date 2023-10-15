#include <stdio.h>
#include <stdlib.h>
#include "list.h"


void stack_initialize(Stack *s)
{
	(*s) = malloc(sizeof(struct stack)) ;
	(*s)->head = NULL ;
	(*s)->count = 0 ;
	return ;
}

int stack_empty(Stack s)
{
	return (s->head == NULL) ;
}

void stack_push(Stack s , int data)
{
	Node newnode ;
	newnode = malloc(sizeof(struct listnode)) ;
	if (newnode==NULL){
		printf("Stack overflow!\n") ;
		return ;
	}
	newnode->data = data ;
	newnode->next = s->head ;
	s->head = newnode ;
	s->count++ ;
}

int stack_pop(Stack s)
{
	if (stack_empty(s)){
		printf("Stack is empty\n") ;
		return 0 ;
	}
	Node temp ;
	int data ;
	temp = s->head ;
	data = s->head->data ;
	s->head = s->head->next ;
	s->count--;
	free(temp) ;
	return data ;
}


void stack_free(Stack stack)
{
	Node temp = stack->head , prev ;
	while (temp!=NULL){
		prev = temp ; 
		temp = temp->next ;
		free(prev) ;
	}
	free(stack) ;
	return ;
}


int *stack_array(Stack stack)
{
	int *array = malloc(stack->count * sizeof(int)) ;
	Node temp = stack->head ; 
	int i = 0 ;
	while (temp != NULL){
		array[i] = temp->data ;
		i++;
		temp = temp->next;
	}

	return array;
}


int stack_count(Stack stack)
{
	return stack->count ;
}



