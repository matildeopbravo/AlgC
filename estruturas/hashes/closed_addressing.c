#include <stdio.h>
#include <stdlib.h>

typedef struct bucket {
    int key;
    int info;
    struct bucket* next;
} * Bucket;

typedef struct thash {
    int size;
    Bucket* tabela;
} * THash;

THash createTable(int N) {
    THash tab = malloc(sizeof(struct thash));
    for (int i = 0; i < N; tab->tabela = NULL, i++)
        ;
    tab->size = N;
    return tab;
}
int hash(int key, int size) {
    return 0;
}

// limitation -> it's gonna check already-rehashed values
int duplicateTable(THash t) {
    int old_size = t->size;
    t->size *= 2;
    t->tabela = realloc(t->tabela, t->size * sizeof(Bucket));
    for (int i = 0; i < old_size; i++) {
        Bucket buck_ant = NULL;
        for (Bucket buck = t->tabela[i]; buck; buck = buck->next) {
            int p = hash(buck->key, t->size);
            if (p != i) {
                if (!buck_ant) {
                    t->tabela[i] = buck->next;
                }
                else {
                    buck_ant->next = buck->next;
                }
                buck->next = t->tabela[p];
                t->tabela[p] = buck;
            }
            else {
                buck_ant = buck;
            }
        }
    }
    return 0;
}

int main() {
    printf("Hello world\n");
}

