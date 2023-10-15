#include <stdio.h>
#include <stdlib.h>

typedef struct listnode* Node ;

struct listnode{
	int data ;
	Node next ;
};

typedef struct stack* Stack ;

struct stack{
	Node head ;
};

void stack_initialize(Stack *s)
{
	(*s) = malloc(sizeof(struct stack)) ;
	(*s)->head = NULL ;
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




