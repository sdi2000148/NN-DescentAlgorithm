typedef struct stack* Stack ;

void stack_initialize(Stack *) ;
int stack_empty(Stack) ;
void stack_push(Stack , int) ;
int stack_pop(Stack) ;
void stack_free(Stack);
