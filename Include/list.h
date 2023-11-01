
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

/* Initialize list */
void list_initialize(List *list);

/* Get the first listnode of list */
Listnode list_head(List list);

/* Get the next listnode of the listnode */
Listnode list_next(Listnode Listnode);

/* Get the data of the listnode */
int listnode_data(Listnode listnode);

/* Insert data to the start of the list */
void list_insert(List list, int data);

/* Remove item from list, return 1 if succeeded, 0 if the item never existed */
int list_remove(List list, int item);

/* Free memory of list */
void list_free(List list);

