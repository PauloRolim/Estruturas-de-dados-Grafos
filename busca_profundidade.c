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

typedef struct adjacencia
{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    /* inserir outros dados necessários */
    ADJACENCIA *cab;

} VERTICE;
