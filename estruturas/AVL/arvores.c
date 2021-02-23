#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum bal { L = -1, B = 0, R = 1 } Bal;
typedef struct avl {
    Bal bal;
    int key, info;
    struct avl *left, *right;
} * AVL;

AVL rotateLeft(AVL tree) {
    AVL aux = tree->right;
    tree->right = aux->left;
    aux->left = tree;
    return aux;
}
AVL rotateRight(AVL tree) {
    AVL aux = tree->left;
    tree->left = aux->right;
    aux->right = tree;
    return aux;
}

bool update_tree(AVL* tree, int key, int info, int* g) {
    return tree;
}
int main() {
    printf("Hello world\n");
}

