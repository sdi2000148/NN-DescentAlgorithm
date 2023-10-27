#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct node *Node;

struct node {
  int value;
  Node left;
  Node right;
  int height;
};




struct avl {
    Node root;
};


static int height(Node N) {
    if(N == NULL) {
        return 0;
    }
    return N->height;
}


static int max(int a, int b) {
    if(a > b) 
        return a;
    else 
        return b;
}

static Node rightRotate(Node y) {
    Node x = y->left, T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static Node leftRotate(Node x) {
    Node y = x->right, T2 = y->left;

    y->left = x;
    x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int getBalance(Node N) {
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

static Node insertNode(Node node, int value) {
    int balance;
    Node newnode;
    if(node == NULL) {
        newnode = malloc(sizeof(struct node));
        newnode->value = value;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->height = 1;
        return newnode;
    }

    if (value < node->value)
        node->left = insertNode(node->left, value);
    else if (value > node->value)
        node->right = insertNode(node->right, value);
    else
        return node;


    node->height = 1 + max(height(node->left), height(node->right));

    balance = getBalance(node);

    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;

}

static Node minValueNode(Node node) {
    Node current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

static Node deleteNode(Node root, int value) {
    Node temp;
    int balance;
    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);

    else if (value > root->value)
        root->right = deleteNode(root->right, value);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {

            if(root->left != NULL) {
                temp = root->left;
            }
            else {
                temp = root->right;
            }

            if(temp == NULL) {
                temp = root;
                root = NULL;
            }
            else 
                *root = *temp;
            free(temp);

        } 
        else {
            temp = minValueNode(root->right);

            root->value = temp->value;

            root->right = deleteNode(root->right, temp->value);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

static int searchNode(Node node, int value) {
    if (node == NULL) {
        return 0; 
    }

    if (value < node->value) {
        return searchNode(node->left, value);
    } else if (value > node->value) {
        return searchNode(node->right, value);
    } else {
        return 1; 
    }
}

static void nodeDestroy(Node node) {
    if(node == NULL)
        return;

    nodeDestroy(node->left);
    nodeDestroy(node->right);

    free(node);
}

static void printPreOrder(Node root) {
    if (root != NULL) {
        printf("%d ", root->value);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}


void avl_initialize(Avl *avl) {
    (*avl) = malloc(sizeof(struct avl));
    (*avl)->root = NULL;
    return;
}


void avl_insert(Avl avl, int value) {
    avl->root = insertNode(avl->root, value);
}


void avl_remove(Avl avl, int value) {
    avl->root = deleteNode(avl->root, value);
}

int avl_search(Avl avl, int value) {
    return searchNode(avl->root, value);
}

void avl_print(Avl avl) {
    printPreOrder(avl->root);
}

void avl_free(Avl avl) {
    nodeDestroy(avl->root);
    free(avl);
}
