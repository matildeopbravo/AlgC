#include <stdio.h>
#include <stdlib.h>

void print_array(int a[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
}
void swap(int* a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int* a, int start, int end) {
    int pivot = a[start];  // not best option mas coiso
    int k = start + 1;  // indice até onde(non inc) estao os menores que o pivot

    for (int i = k; i <= end; i++) {
        if (a[i] < pivot) {
            swap(a, i, k);
            k++;
        }
    }
    swap(a, start, k - 1);
    return k - 1;
}

void merge(int* a, int N, int m) {
    int aux[N];

    for (int i = 0; i < N; i++) aux[i] = a[i];

    for (int i = 0, j = m, k = 0; k < N; k++) {
        if (j == N || aux[i] < aux[j])
            a[k] = aux[i++];
        else
            a[k] = aux[j++];
    }
}

void quicksort(int* a, int N) {
    if (N > 1) {
        int p = partition(a, 0, N - 1);
        quicksort(a, p);
        quicksort(a + p + 1, N - (p + 1));
    }
}
void mergesort(int* v, int N) {
    if (N > 1) {
        int m = N / 2;
        mergesort(v, m);
        mergesort(v + m, N - m);
        merge(v, N, m);
    }
}

int main() {
    int N = 8;
    int a[] = {7, 10, 20, 30, 1, 3, 5, 8};
    mergesort(a, N);
    print_array(a, N);
}
