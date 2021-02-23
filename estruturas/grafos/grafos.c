#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NV 4  // numero de vertices
#define NE 0  // peso da aresta que não existe
#define V 10
#define BRANCO 0
#define CINZENTO 1
#define PRETO 2

// grafos em matriz de adjacencia
typedef int GraphMat[NV][NV];

// grafos em listas de adjacencia
typedef struct aresta {
    int destino, peso;
    struct aresta* prox;
} * ListaAdj;
// hidden pointers bad mas uni é assim

typedef ListaAdj Graph[NV];

void matTolist(GraphMat mat, Graph grafo) {
    ListaAdj tmp;
    for (int i = 0; i < NV; i++) {
        grafo[i] = NULL;
        for (int j = NV - 1; j >= 0; j--) {
            if (mat[i][j] != NE) {
                tmp = malloc(sizeof(struct aresta));
                *tmp = (struct aresta){
                    .destino = j,
                    .peso = mat[i][j],
                    .prox = grafo[i],
                };
                grafo[i] = tmp;
            }
        }
    }
}
void printMat(GraphMat mat) {
    for (int i = 0; i < NV; i++) {
        for (int j = 0; j < NV; j++) {
            printf("%d ", mat[i][j]);
        }
        putchar('\n');
    }
}
// supondo que se recebe uma array inicializado a NE
// void listTomat (Graph grafo, GraphMat mat) {
//    for(int i = 0; i < NV ; i++) {
//        for (ListaAdj aux = grafo[i] ; aux ; aux = aux->prox) {
//            mat[i][aux->destino] = aux->peso;
//        }
//    }
//}
void listTomat(Graph grafo, GraphMat mat) {
    for (int i = 0; i < NV; i++) {
        ListaAdj tmp = grafo[i];
        for (int j = 0; j < NV; j++) {
            if (!tmp || tmp->destino > j) {
                mat[i][j] = NE;
            }
            else {
                mat[i][j] = tmp->peso;
                tmp = tmp->prox;
            }
        }
    }
}
void printList(Graph grafo) {
    for (int i = 0; i < NV; i++) {
        printf("|%d| ", i);
        for (ListaAdj tmp = grafo[i]; tmp; tmp = tmp->prox) {
            printf("->");
            printf(" %d ", tmp->destino);
        }
        putchar('\n');
    }
}

int contaArestas(Graph g) {
    int count = 0;
    for (int i = 0; i < V; i++) {
        for (ListaAdj x = g[i]; x; x = x->prox, count++)
            ;
    }
    return count;
}

int outDegree(Graph g) {
    int max = 0;
    for (int i = 0; i < V; i++) {
        int count = 0;
        for (ListaAdj l = g[i]; l; l = l->prox, count++)
            ;
        max = count > max ? count : max;
    }
    return max;
}
int haAresta(Graph g, int o, int d) {
    ListaAdj x;
    for (x = g[o]; x && x->destino != d; x = x->prox)
        ;
    return x != NULL;
}
// não funciona para ciclos e grafos não orientados
int haCaminho_pre(Graph g, int o, int d) {
    int r = o == d;
    for (ListaAdj x = g[o]; !r && x; x = x->prox) {
        r = haCaminho_pre(g, x->destino, d);
    }
    return r;
}
/////////////////// DEPTH-FIRST  ///////////////////////////

// T_haCaminho(V,E) =  V + E
// array of enums/bools would be better but I don't make the rules
int haCaminho(Graph g, int o, int d, int vis[]) {
    int r = o == d;
    vis[o] = 1;
    for (ListaAdj x = g[o]; !r && x; x = x->prox) {
        int dest = x->destino;
        if (!vis[dest]) {
            r = haCaminho(g, dest, d, vis);
        }
    }
    return r;
}
// another trick cause I'm sick in the (over)head
// pushes one byte instead of four to the stack
// though it's not threadsafe and it looks more cryptic
int haCaminho2(Graph g, int o, int d, bool b) {
    static int vis[V] = {0};
    if (b) {
        memset(vis, 0, V);
        b = false;
    }
    int r = o == d;
    vis[o] = 1;
    for (ListaAdj x = g[o]; !r && x; x = x->prox) {
        int dest = x->destino;
        if (!vis[dest]) {
            r = haCaminho2(g, dest, d, b);
        }
    }
    return r;
}

void test_caminhos(Graph grafo) {
    int visitados[V] = {0};
    char* s = haCaminho(grafo, 0, 2, visitados) ? "" : "não";
    printf("%s existe caminho\n", s);
}

int alcancaveis_DF(Graph g, int o, int vis[]) {
    int count = 1;
    vis[o] = 1;
    for (ListaAdj x = g[o]; x; x = x->prox) {
        int dest = x->destino;
        if (!vis[dest]) {
            count += alcancaveis_DF(g, dest, vis);
        }
    }
    return count;
}

/////////////////////// BREADTH-FIRST ////////////////////////////////////////

int quantos_alcancaveis_BF(Graph g, int o) {
    int orla[V], inicio, fim;
    int count = 0;
    int cor[V] = {BRANCO};  // O(V)
    inicio = fim = 0;

    orla[fim++] = o;

    for (; inicio < fim; count++) {
        int v = orla[inicio++];  // dequeue
        cor[v] = PRETO;
        for (ListaAdj x = g[v]; x; x = x->prox) {
            if (cor[x->destino] == BRANCO) {
                orla[fim++] = x->destino;
            }
        }
    }
    return count;
}
int arvore_BF(Graph g, int o, int pais[], int alc[]) {
    int orla[V], inicio, fim;
    int count = 0;
    int cor[V] = {BRANCO};  // O(V)
    for (int i = 0; i < V; i++) {
        alc[i] = 0;
        pais[i] = -2;
    }
    inicio = fim = 0;
    pais[o] = -1;
    orla[fim++] = o;

    while (inicio < fim) {
        int v = orla[inicio++];  // dequeue
        cor[v] = PRETO;
        alc[v] = 1;
        for (ListaAdj x = g[v]; x; x = x->prox) {
            if (cor[x->destino] == BRANCO) {
                orla[fim++] = x->destino;
                pais[x->destino] = v;
            }
        }
    }
    return count;
}
// T_dijkstra(V,E) = V + V + T_addOrla
//                  + T_selecOrla  + V*T_AddOrla  +(E - V)
// pseudo dijkstra

// int dijkstra(Graph g, int o, int alc[], int pais[], int w[]) {
//    int orla[V], inicio, fim;
//    int count = 0;
//    int cor[V] = {BRANCO};  // O(V)
//    for (int i = 0; i < V; i++) {
//        alc[i] = 0;
//        pais[i] = -2;
//    }
//    inicio = fim = 0;
//    pais[o] = -1;
//    // add  to  to orla
//
//    while (tam_orla > 0) {
//        ///////////// remove from orla
//        cor[v] = PRETO;
//        alc[v] = 1;
//        for (ListaAdj x = g[v]; x; x = x->prox) {
//            int new = w[v] + x->peso;
//            int current = w[x->destino];
//            if (cor[x->destino] == BRANCO) {
//                w[x->destino] = new;
//                orla[fim++] = x->destino;
//                pais[x->destino] = v;
//            }
//            else if (cor[x->destino] == CINZENTO && new < current) {
//                w[x->destino] = new;
//                pais[x->destino] = v;
//            }
//        }
//    }
//    return count;
//}

int main() {
    GraphMat mat = {{0, 2, 0, 0}, {2, 0, 3, 1}, {0, 3, 0, 0}, {0, 1, 0, 0}};
    Graph grafo = {NULL};
    GraphMat new_mat;
    matTolist(mat, grafo);
}
