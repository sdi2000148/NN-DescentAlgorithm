#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_initialize(List *list) {
    (*list) = malloc(sizeof(struct list));
    (*list)->head = NULL;
    return;
}

Listnode list_head(List list) {
    return list->head;
}

Listnode list_next(Listnode node) {
    return node->next;
}

int listnode_data(Listnode node) {
    if(node == NULL) {
        return -1; // indices, we don't care for negatives
    }

    return node->data;
}

void list_insert(List list, int data) {
    Listnode newNode = malloc(sizeof(struct listnode));

    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;

    return;
}

int list_remove(List list, int item) {
    Listnode temp = list_head(list);
    Listnode nodeToRemove;

    if(temp->data == item) {
        list->head = temp->next;
        free(temp);
        return 1;
    }

    while(temp->next != NULL) {
        if(temp->next->data == item) {
            nodeToRemove = temp->next;
            temp->next = temp->next->next;
            free(nodeToRemove);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void list_free(List list) {
    Listnode node = list->head, prev;

    while(node != NULL) {
        prev = node;
        node = node->next;
        free(prev);
    }
    free(list);
    return;
}




