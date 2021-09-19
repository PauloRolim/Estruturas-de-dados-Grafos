/*Implementação de Busca em Profundidade, utilizando uma lista de adjacências, e aplicando
cores aos vértices visitados*/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

typedef struct adjacencia //na verdade essa estrutura é uma lista ligada
{
    int vertice; //vertice de destino da adjacencia
    TIPOPESO peso;
    struct adjacencia *prox; //próximo vértice da lista
} ADJACENCIA;

typedef struct vertice
{
    /* inserir outros dados necessários */
    ADJACENCIA *cab; // o vértice só tem a cabeça da sua lista de adjacências, suas arestas

} VERTICE;

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

void profundidade(GRAFO *g)
{
    int cor[g->vertices]; /*arranjo de cores para colorir os vertices visitados.
                            o índice do vertice no arranjo adj em GRAFO deve coincidir 
                            com o arranjo de cores, para possibilitar o relacionamento
                            entre a cor designada e o vértice do grafo*/

    int u;

    for (u = 0; u < g->vertices; u++)
    {
        cor[u] = BRANCO;
    }

    for (u = 0; u < g->vertices; u++)
    {
        if (cor[u] == BRANCO)
        {
            visitaP(g,u,cor);
        }
        
    }
        
}

void visitaP(GRAFO *g, int u, int *cor)
{
    cor[u] = AMARELO;
    ADJACENCIA *v = g->adj[u].cab;

    while (v)
    {
        if (cor[v->vertice] == BRANCO)
        {
            visitaP(v,g->vertices,cor);
            v = v->prox;
        }
        cor[u] = VERMELHO;
    }
    
}

