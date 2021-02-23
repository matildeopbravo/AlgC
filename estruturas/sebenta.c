#include <stdio.h>
#include <stdlib.h>
#define LIVRE 0
#define APAGADO 1
#define OCUPADO 2

// 44
typedef struct llint {
    int value;
    struct llint* next;
} * LInt;
typedef struct avl {
    int value;
    int bal, deleted;
    struct avl *left, *right;
} * AVL;

AVL fromList(LInt l, int N) {
    AVL nodo = NULL;
    if (N > 0) {
        nodo = malloc(sizeof(struct avl));
        nodo->value = l->value;
        nodo->deleted = 0;
        nodo->left = fromList(l->next, N / 2);
        nodo->right = fromList(l->next, N - N / 2 - 1);
    }
    return nodo;
}
// 46
struct entry {
    int value, status;
};

typedef struct thash {
    int ocupados, tamanho;
    struct entry* tabela;
} * THash;
// 47
AVL rotateRight(AVL a) {
    AVL aux = a->left;
    a->left = aux->right;
    aux->right = a;
    return aux;
}
AVL spine(AVL a) {
    if (a != NULL) {
        while (a->left != NULL) {
            a = rotateRight(a);
        }
        a->right = spine(a->right);
    }
    return a;
}

