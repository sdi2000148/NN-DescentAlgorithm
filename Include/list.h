#pragma once

typedef struct stack* Stack ;

typedef struct listnode* Node ;

struct listnode{
	int data ;
	Node next ;
};

typedef struct stack* Stack ;

struct stack{
	Node head ;
    int count ;
};

void stack_initialize(Stack *) ;
int stack_empty(Stack) ;
void stack_push(Stack , int) ;
int stack_pop(Stack) ;
void stack_free(Stack);
int *stack_array(Stack);
int stack_count(Stack);