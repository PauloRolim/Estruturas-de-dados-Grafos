/* 
   ** Uma versão em C++ do algoritmo de Tarjan para localizar pontes num grafo.
   ** A vantagem dessa abordagem está na complexidade que fica na ordem de O(V+E).
*/
#include<iostream>
#include <list>
#define NIL -1
using namespace std;
 
// Classe que representa um grafo não direcionado
class Graph
{
    int V;    // Número de vértices
    list<int> *adj;    // Lista de adjacencias com alocação dinâmica de memória
    void bridgeUtil(int v, bool visited[], int disc[], int low[],
                    int parent[]);
public:
    Graph(int V);   // Construtor do grafo
    void addEdge(int v, int w);   // função que adiciona uma aresta ao grafo
    void bridge();    // função que exibe na tela as possíveis pontes no grafo
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // O grafo é não direcionado
}
 
/* 
   ** Uma função recursiva que encontra e exibe na tela as pontes utilizando
   ** travessia por meio de busca em profundidade - DFS.
   ** u --> variável que diz o vértice que será visitado em seguida;
   ** visited[] --> armazena os vértices visitados;
   ** disc[] --> armazena o tempo de descoberta dos vértices visitados;
   ** parent[] --> armazena os vértices adjacentes da árvore de busca em profundidade
*/
void Graph::bridgeUtil(int u, bool visited[], int disc[],
                                  int low[], int parent[])
{
    /* 
      A static variable is used for simplicity, we can
      avoid use of static variable by passing a pointer.
    */
    static int time = 0;
 
    // Marca o vértice atual como visitado
    visited[u] = true;
 
    
    // Inicializa o tempo de descoberta e o low value
    disc[u] = low[u] = ++time;
 
    
    // Percorre todos os vértices adjacentes ao vértice fornecido
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v é o atual adjacente a u
 
        // Se v ainda não foi visitado, então retorna a ele
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
 
                        
            /*Verifica se a subarvore de raiz v está conectada
            a um dos vértives antecedentes a u*/
            low[u]  = min(low[u], low[v]);
 
            /*Se o menor vértice alcançável pela subarvore
             de raiz v está abaixo de u na árvore de DFS, então a aresta u-v
             é uma ponte*/
            if (low[v] > disc[u])
            cout << u <<" " << v << endl;
        }
 
        // Atualiza o low value de u no vetor parent[]
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}
 

/* Fução baseada na busca em profundidade para encontrar todas as pontes. Chama
   recursivamente a fução bridgeUtil().
*/
void Graph::bridge()
{

    // Marca todos os vértices como não visitado
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
 
    
    // Inicializa os vetores parent[] e visited[]
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
    }
 
    //Chama recursivamente a função bridgeUtil() para encontrar as
    // pontes na árvore de busca em profundidade com vértice em "i"
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i, visited, disc, low, parent);
}
 

int main()
{
    
    cout << "\nPontes no primeiro grafo " << endl;
    Graph g1(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(0, 3);
    g1.addEdge(0, 4);
    g1.addEdge(1, 2);
    g1.addEdge(3, 4);
    g1.bridge();
 
    cout << "\nPontes no segundo grafo " << endl;
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    g2.bridge();
 
    cout << "\nPontes no terceiro grafo " << endl;
    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.bridge();
 
    return 0;
}