#include <stdio.h>
#include <stdlib.h>
#define HSIZE 11
#define STATUS_FREE 0
#define STATUS_USED 1

typedef struct bucket {
    int status;
    int key;
    int info;
} Bucket;
typedef Bucket HashTable[HSIZE];

int main() {}

