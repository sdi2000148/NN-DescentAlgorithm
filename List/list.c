#include <stdio.h>

#include <stdlib.h>

#include "list.h"

struct listnode {
  int data;
  Listnode next;
};

struct list {
  Listnode head;
  Listnode tail;
};

void list_initialize(List * list) {
  ( * list) = malloc(sizeof(struct list));
  ( * list) -> head = NULL;
  ( * list) -> tail = NULL;
  return;
}

Listnode list_head(List list) {
  return list -> head;
}

Listnode list_tail(List list) {
  return list -> tail;
}

Listnode list_next(Listnode node) {
  return node -> next;
}

int listnode_data(Listnode node) {
  if (node == NULL) {
    return -1;
  }

  return node -> data;
}

void list_insert(List list, int data) {
  Listnode newNode = malloc(sizeof(struct listnode));
  newNode -> data = data;
  newNode -> next = NULL;

  if (list -> tail == NULL) {
    list -> head = newNode;
    list -> tail = newNode;
  } else {
    list -> tail -> next = newNode;
    list -> tail = newNode;
  }

  return;
}

int list_remove(List list, int item) {
  Listnode temp = list_head(list);
  Listnode nodeToRemove;

  if (temp == NULL) return 0;

  if (temp -> data == item) {
    list -> head = temp -> next;

    if (list -> head == NULL) {
      list -> tail = NULL;
    }
    free(temp);
    return 1;
  }

  while (temp -> next != NULL) {
    if (temp -> next -> data == item) {
      nodeToRemove = temp -> next;
      temp -> next = temp -> next -> next;
      if (temp -> next == NULL) {
        list -> tail = temp;
      }
      free(nodeToRemove);

      return 1;
    }
    temp = temp -> next;
  }
  return 0;
}

int list_search(List list, int item) {
  Listnode node = list_head(list);

  while (node != NULL) {
    if (listnode_data(node) == item) {
      return 1;
    }

    node = list_next(node);
  }

  return 0;
}

void list_free(List list) {
  Listnode node = list -> head, prev;

  while (node != NULL) {
    prev = node;
    node = node -> next;
    free(prev);
  }
  free(list);
  return;
}