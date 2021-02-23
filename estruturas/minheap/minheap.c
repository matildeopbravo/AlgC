#include <stdio.h>
#include <stdlib.h>
#define PARENT(i) (i - 1) / 2
#define CHILD(i) 2 * i + 1

typedef int Elem;  // elementos da heap.
typedef struct {
    int size;
    int used;
    Elem* value;
} Heap;

void initHeap(Heap* h, int size) {
    *h = (Heap){.size = size, .used = 0, .value = malloc(sizeof(Elem) * size)};
}

void swap(Elem* value, int index_a, int index_b) {
    int tmp = *(value + index_a);
    value[index_a] = *(value + index_b);
    *(value + index_b) = tmp;
}
void bubble_up(Heap* h, int index) {
    int parent = PARENT(index);
    while (index > 0 && parent > h->value[index]) {
        swap(h->value, index, parent);
        index = parent;
        parent = PARENT(index);
    }
}

void bubble_upRec(Heap* h, int last_index) {
    int index_parent = (last_index - 1) / 2;
    if (*(h->value + last_index) < h->value[index_parent]) {
        swap(h->value, index_parent, last_index);
        bubble_upRec(h, index_parent);
    }
}

void insertHeap(Heap* h, Elem x) {

    if (h->size == h->used) {
        h->size *= 2;
        h->value = realloc(h->value, h->size * sizeof(Elem));
    }
    h->used++;
    *(h->value + h->used - 1) = x;
    bubble_up(h, h->used - 1);
}

void bubble_downRec(
    Elem* values, int size, int index_parent, int number_children) {
    int child_index;
    if (number_children > 1) {
        child_index =
            number_children == 2 ? 1 : (values[1] < values[2] ? 1 : 2);
        if (values[0] > values[child_index]) {
            swap(values, 0, child_index);
        }
        if (child_index == 1) {
        }
        bubble_downRec(
            values + child_index,
            size,
            index_parent,
            size - CHILD(index_parent));
    }
}
void bubble_down(Heap* h, int parent) {
    int child = CHILD(parent);
    while (child < h->used) {
        if (child + 1 < h->used && h->value[child + 1] < h->value[child]) {
            child = child + 1;
        }
        if (h->value[parent] < h->value[child]) break;
        swap(h->value, child, parent);
        parent = child;
        child = CHILD(parent);
    }
}

void extractMin(Heap* h, Elem* x) {
    *x = *h->value;
    *(h->value) = h->value[h->used-- - 1];
    bubble_down(h, 0);
}

int main() {
    Heap h = {0};
    initHeap(&h, 100);
    int x;

    insertHeap(&h, 5);
    insertHeap(&h, 13);
    insertHeap(&h, 8);
    insertHeap(&h, 20);
    insertHeap(&h, 14);
    insertHeap(&h, 16);
    insertHeap(&h, 23);
    insertHeap(&h, 21);
    insertHeap(&h, 25);
    insertHeap(&h, 35);
    insertHeap(&h, 15);
    insertHeap(&h, 33);
    insertHeap(&h, 70);
    insertHeap(&h, 85);
    insertHeap(&h, 29);
    h.value[11] = 13;
    bubble_up(&h, 11);
    h.value[1] = 33;

    for (int i = 0; i < h.used; i++) {
        printf("%d\n", *(h.value + i));
    }

    //  extractMin(&h,&x);
    //  printf("O min retirado é %d\n",x);
    //
    //  for (int i = 0; i < h.used ; i++) {
    //      printf("%d\n",*(h.value+i));
    //  }
    //
    free(h.value);
    return 0;
}
