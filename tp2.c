/*
Matteus Guilherme de Souza - 769816
Algoritmos e Estruturas de Dados 2 - 2023-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct noh Noh;

struct noh
{
    int rotulo;
    int custo;
    Noh *prox;
};

typedef struct grafo *Grafo;

struct grafo
{
    Noh **A;
    int n; // # Vértices
    int m; // # Arestas
};

// Função para inicializar um grafo G com n-1 vértices e vazio de arestas
Grafo inicializaGrafo(int n)
{
    int i;
    Grafo G = malloc(sizeof *G);
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(Noh *));
    for (i = 0; i < n; i++)
    {
        G->A[i] = NULL;
    }
    return G;
}

// Função de inserção de um arco v-w em um grafo G. Caso já exista este arco, não faz nada
void insereArcoGrafo(Grafo G, int v, int w, int c)
{
    Noh *p;
    for (p = G->A[v]; p != NULL; p = p->prox)
    {
        if (p->rotulo == w)
        {
            return;
        }
    }
    p = malloc(sizeof(Noh));
    p->rotulo = w;
    p->custo = c;
    p->prox = G->A[v];
    G->A[v] = p;
    G->m++;
}

Grafo liberaGrafo(Grafo G)
{
    int i;
    Noh *p;
    for (i = 0; i < G->n; i++)
    {
        p = G->A[i];
        while (p != NULL)
        {
            G->A[i] = p;
            p = p->prox;
            free(G->A[i]);
        }
        G->A[i] = NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;
}

void buscaProfOrdTopoR(Grafo G, int v, int *visitado, int *ordTopo, int *protulo_atual)
{
    int w;
    Noh *p;
    visitado[v] = 1;
    p = G->A[v];
    while (p != NULL)
    {
        w = p->rotulo;
        if (visitado[w] == 0)
        {
            buscaProfOrdTopoR(G, w, visitado, ordTopo, protulo_atual);
        }
        p = p->prox;
    }
    ordTopo[--(*protulo_atual)] = v;
}

void ordenacaoTopologica(Grafo G, int *ordTopo)
{
    int v, rotulo_atual, *visitado;
    visitado = (int*) malloc(G->n*sizeof(int));
    if(visitado == NULL){
        printf("Erro\n");
        exit(2);
    }

    for (v = 0; v < G->n; v++)
    {
        visitado[v] = 0;
        ordTopo[v] = -1;
    }
    rotulo_atual = G->n;
    for (v = 0; v < G->n; v++)
    {
        if (visitado[v] == 0)
        {
            buscaProfOrdTopoR(G, v, visitado, ordTopo, &rotulo_atual);
        }
    }
}

int CalcVel(Grafo G){
    int *velocidade = (int*)malloc(G->n * sizeof(int));
    int *ordTopo = (int*)malloc(G->n * sizeof(int));
    int v, w, custo, vel_final;
    Noh* p;
    for (int i = 0; i < G->n; i++)
    {
        velocidade[i] = INT_MIN;
    }

    ordenacaoTopologica(G, ordTopo);

    velocidade[0] = 0;

    for (int i = 0; i < G->n; i++)
    {
        v = ordTopo[i];
        p = G->A[v];
        while (p != NULL)
        {
            w = p->rotulo;
            custo = p->custo;
            if (velocidade[w] < velocidade[v] + custo)
            {
                velocidade[w] = velocidade[v] + custo;
            }
            p = p->prox;
        }
        
    }
    vel_final = velocidade[G->n -1];
    free(velocidade);
    free(ordTopo);
    return vel_final;
}

int main(){
    int n, m, v, velocidade;

    Grafo G;

    scanf("%d %d %d", &n, &m, &v);
    fflush(NULL);

    G = inicializaGrafo(n);

    for (int i = 0; i < m; i++)
    {
        int u, w, cost;
        scanf("%d %d %d", &u, &w, &cost);
        insereArcoGrafo(G, u, w, cost);
    }

    velocidade = CalcVel(G);
    velocidade = velocidade + v;

    liberaGrafo(G);

    printf("%d\n", velocidade);
}