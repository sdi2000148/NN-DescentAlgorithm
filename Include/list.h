
#pragma once

typedef struct list *List;

typedef struct listnode *Listnode;

struct listnode {
    int data;
    Listnode next;
};


struct list {
    Listnode head;
};


void list_initialize(List *list);
Listnode list_head(List list);
Listnode list_next(Listnode Listnode);
int listnode_data(Listnode listnode);
void list_insert(List list, int data);
int list_remove(List list, int item);
void list_free(List list);

