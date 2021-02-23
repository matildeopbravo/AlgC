#include <stdio.h>
#include <stdlib.h>

typedef enum bal { Left = -1, Bal = 0, Right = 1 } Balance;

typedef struct node {
    int value;
    Balance bal;
    struct node *left, *right;
} * AVL;
// O(N-1) ~ O(N)
int deepest(AVL* a) {
    AVL l, r;
    int hl, hr, h;
    if (!*a)
        h = 0;
    else {
        l = (*a)->left;
        r = (*a)->right;
        hl = deepest(&l);
        hr = deepest(&r);
        if ((hl > 0) && (hl > hr)) {
            *a = l;
            h = hl + 1;
        }
        else if (hr > 0) {
            *a = r;
            h = hr + 1;
        }
        else
            h = 1;
    }
    return h;
}
// O(log N)
int my_deepest(AVL* a) {

    AVL l, r;
    int h;
    if (!*a)
        h = 0;
    else {
        l = (*a)->left;
        r = (*a)->right;
        if (l && (*a)->bal == Left) {
            h = my_deepest(&l) + 1;
        }
        else if (r) {
            h = my_deepest(&r) + 1;
            *a = r;
        }
        else {
            h = 1;
        }
    }
    return h;
}

AVL arrayToTree(int* arr, int N, int* h) {
    if (N > 0) {
        int hl, hr;
        int mid = N / 2;
        AVL node = malloc(sizeof(struct node));
        node->value = arr[mid];
        node->left = arrayToTree(arr, mid, h);
        hl = *h;
        node->right = arrayToTree(arr + mid + 1, N - mid - 1, h);
        hr = *h;
        *h = (hl > hr ? hl : hr) + 1;
        node->bal = hr - hl;
        return node;
    }
    else {
        *h = 0;
        return NULL;
    }
}
void print_tree(AVL tree) {
    if (tree) {
        print_tree(tree->left);
        printf("%d-%d\n", tree->value, tree->bal);
        print_tree(tree->right);
    }
}
int main() {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int h = 0;
    AVL tree = arrayToTree(arr, 8, &h);
    print_tree(tree);
    putchar('\n');
    printf("%d\n", h);
    return 0;
}
