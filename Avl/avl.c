#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "list.h"

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
    if(N == NULL) { // empty 
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

    // rotate x and y to the right 
    x->right = y; 
    y->left = T2;

    // update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static Node leftRotate(Node x) {
    Node y = x->right, T2 = y->left;

    // rotate x and y to the left
    y->left = x;
    x->right = T2;

    // update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int getBalance(Node N) {
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right); // balance factor used to determine the update to be made in each step of the recursion 
}

static Node insertNode(Node node, int value, int *result) {
    int balance;
    Node newnode;
    if(node == NULL) { // and of the tree
        newnode = malloc(sizeof(struct node));
        newnode->value = value;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->height = 1;
        *result = 1; // insertion succeeded 
        return newnode;
    }

    if (value < node->value) // smaller value, go left
        node->left = insertNode(node->left, value, result);
    else if (value > node->value) // higher value, go right
        node->right = insertNode(node->right, value, result);
    else // value found
        return node;
    
    
    node->height = 1 + max(height(node->left), height(node->right)); // update height

    balance = getBalance(node); // get the balance factor

    if (balance > 1 && value < node->left->value) // case 1: right rotation
        return rightRotate(node);

    if (balance < -1 && value > node->right->value) // case 2: left rotation
        return leftRotate(node);

    if (balance > 1 && value > node->left->value) { // case 3: left right rotation
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->value) { // case 4: right left rotation
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;

}

static Node minValueNode(Node node) {
    Node current = node;

    while (current->left != NULL)
        current = current->left; 

    return current; // minimum value of the tree of node
}

static Node deleteNode(Node root, int value, int *result) {
    Node temp;
    int balance;
    if (root == NULL) // empty tree
        return root;

    if (value < root->value) // smaller value, go left
        root->left = deleteNode(root->left, value, result);

    else if (value > root->value) // higher value, go right
        root->right = deleteNode(root->right, value, result);

    else { // value found
        if ((root->left == NULL) || (root->right == NULL)) { // node has 1 child at most

            if(root->left != NULL) { // node has left child 
                temp = root->left;
            }
            else { 
                temp = root->right;
            }

            if(temp == NULL) { // node doesn't have any children
                temp = root;
                root = NULL;
            }
            else // node has right child
                *root = *temp;
            *result = 1; // removal succeeded
            free(temp);

        } 
        else { // node has 2 children
            temp = minValueNode(root->right); // get minumum value of right subtree  

            root->value = temp->value; // node value with the value 

            root->right = deleteNode(root->right, temp->value, result);
        }
    }

    if (root == NULL)
        return root;


    // update height
    root->height = 1 + max(height(root->left), height(root->right));

    balance = getBalance(root); // get the balance factor
    if (balance > 1 && getBalance(root->left) >= 0) // case 1: right rotation
        return rightRotate(root); 

    if (balance > 1 && getBalance(root->left) < 0) { // case 2: left right rotation
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) // case 3: left rotation
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) { // case 4: right left rotation
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

static int searchNode(Node node, int value) {
    if (node == NULL) { // value wasn't found
        return 0; 
    }

    if (value < node->value) { // smaller value, go left
        return searchNode(node->left, value);
    } else if (value > node->value) { // higher value, go right
        return searchNode(node->right, value);
    } else {
        return 1; 
    }
}

static void nodeDestroy(Node node) { // destruction of the subtree of the node
    if(node == NULL)
        return;

    nodeDestroy(node->left);
    nodeDestroy(node->right);

    free(node);
}

static void copyToList(Node node, List list) { // copy all the values to a list
    if (node != NULL) {
        copyToList(node->left, list);
        list_insert(list, node->value);
        copyToList(node->right, list);
    }
}


/* General avl apis */

void avl_initialize(Avl *avl) {
    (*avl) = malloc(sizeof(struct avl));
    (*avl)->root = NULL;
    return;
}


int avl_insert(Avl avl, int value) {
    int result = 0;
    avl->root = insertNode(avl->root, value, &result);
    return result;
}


int avl_remove(Avl avl, int value) {
    int result = 0;
    avl->root = deleteNode(avl->root, value, &result);
    return result;
}

int avl_search(Avl avl, int value) {
    return searchNode(avl->root, value);
}


void avl_copyToList(Avl avl, List list) {
    copyToList(avl->root, list);
}

void avl_free(Avl avl) {
    nodeDestroy(avl->root);
    free(avl);
}
