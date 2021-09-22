/*  Algoritmo de Fleury
 ** Considere um grafo onde todos os vértices fazem parte do mesmo componente, e existem no máximo dois
 ** vértices de grau ímpar. O algoritmo começa em um vértice de grau ímpar ou, se o grfo não tiver nenhum, 
 ** ele começa com um vértice escolhido arbitrariamente. Em cada etapa, ele escolhe a próxima aresta no caminho 
 ** para ser aquela cuja exclusão não desconectaria o gráfico, a menos que não haja tal aresta, caso em que ele 
 ** escolhe a aresta restante no vértice atual. Em seguida, ele se move para o outro ponto final dessa aresta e exclui a aresta.
 ** No final do algoritmo, não há arestas restantes, e a sequência a partir da qual as arestas foram escolhidas 
 ** forma um ciclo Euleriano se o grafo não tiver vértices de grau ímpar, ou um caminho Euleriano 
 ** se houver exatamente dois vértices de grau ímpar.
 ** A complexidade é de O(E+V)², porque para localizar as arestas que são pontes (função isValidNextEdge()), é preciso realizar a Busca 
 ** em profundidade logo em seguinda remove-se uma aresta, depois repete a DFS e depois disso a aresta removida é adicionada novamente.
*/

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#define V 5

using namespace std;

void removeEdge(vector<int> graph[], int u, int v) //função utilizada para remover uma aresta do grafo
{
    vector<int>::iterator it; //

    it = find(graph[v].begin(), graph[v].end(), u);
    *it = -1;

	it = find(graph[u].begin(), graph[u].end(), v);
    *it = -1;
}

void addEdge(vector<int> graph[], int u, int v) //função utilizada para adicionar uma aresta no grafo
{
    graph[u].emplace_back(v); //insere um novo elemento no final do vetor, logo após o último elemnto.
    graph[v].emplace_back(u); //esse novo elemento é constrído utilizando o argumento "u" e "v" fornecidos ao construtor.
}

int dfsCount(vector<int> graph[], int u, vector<bool>& visited) //função de contagem de vértices da busca em profundidade
{
   visited[u] = true; 
   int count = 1;

   //Recursão para contar os vértices adjacentes ao vértice fornecido no argumento "u"
   for (auto av : graph[u])
   {
        if (av != -1 && !visited[av])
            count += dfsCount(graph, av, visited);
   }
   return count;
}

void dfs(vector<int> graph[], int v, vector<bool>& visited) //função que realiza a busca em profundidade
{                                                           //marca os vértices como "visitado"    
    visited[v] = true;
    for (auto av : graph[v])//percorre todo o grafo
        if (!visited[av]) //se houver um vértice não visitado
            dfs(graph, av, visited); //chama recursivamente e marca o vértice como visitado
}

bool isValidNextEdge(vector<int> graph[], int u, int v) // A aresta entre "u-v" é válida se ocorrer um dos seguintes casos:
{                                                       // 1) Se v for o único vértice adjacente a u;                                      
	int count = 0;                                      // 2) Se houverem múltiplas arestas adjacentes, e a aresta "u-v" não for uma ponte;
    for (auto av : graph[u])                            
    {
        if (av != -1)
            count++;
    }
    if (count == 0)
        return false;
    if (count == 1)
	    return true;

    vector<bool> visited(V, false);
    int count1 = dfsCount(graph, u, visited);

    removeEdge(graph, u, v);                        // Para checar se "u-v" é uma ponte:
    fill(visited.begin(), visited.end(), false);    // 1) contam-se os vértices alcançaveis por meio de "u";
                                                    // 2) Remove-se o vértice "u-v", depois de removido, conta-se novamente os vértices alcançaveis por meio de "u";
    int count2 = dfsCount(graph, u, visited);       // 3) Adiciona-se novamente o vértice "u-v" ao grafo;
                                                    // 4) Se o contator "count1" for maior que "count2", a aresta "u-v" é uma ponte;
    addEdge(graph, u, v);

    return (count1 > count2) ? false : true;
}

bool isConnected(vector<int> graph[]) //Função que checa se há conexão entre os vértices do grafo
{
    vector<bool> visited(V, false);

    // Procura um vértice cujo grau seja maior que zero;
    int i = 0;
	for (i = 0; i < V; i++)
        if (graph[i].size() != 0)
            break;

    // Se não houver nenhum vértice no grafo, retorna verdadeiro
    if (i == V)
        return true;

    
    // Chama a busca em profundidade de um vértice que possui grau maior que zero
    dfs(graph, i, visited);

    // Verifica se todos os vértices com grau diferente de zero foram visitados
    for (i = 0; i < V; i++)
        if (visited[i] == false && graph[i].size() > 0)
            return false;

    return true;
}

void eulerCycle(vector<int> graph[], int u)
{                                           // Função recursiva para encontrar o ciclo euleriano
	    vector<int>::iterator it;

    for (auto av : graph[u]) //Percorre todo o grafo;
    {
        if (av != -1 && isValidNextEdge(graph, u, av)) //Checa se a próxima aresta é válida;
        {
            cout << u << "-" << av << "  "; //exibe na tela o vértice por onde passou
            removeEdge(graph, u, av); //remove o vértice do grafo
            eulerCycle(graph, av); //chama novamente a função, e passa para o próximo vértice
        }
    }
    
}

int isEulerian(vector<int> graph[]) //Função que verifica se o grafo é euleriano
{
    
    // Verifica se todos os vértices com grau maior que zero estão conectados
    if (isConnected(graph) == false)
        return 0;

    // Conta quantos vértices tem grau ímpar
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (graph[i].size() & 1)
            odd++;

    if (odd > 2)                        //A função retorna o seguinte:
        return 0;                       // 0 -> se o grafo não for euleriano;
                                        // 1 -> se o grafo tiver um caminho euleriano (grafo semi-euleriano)
    return (odd == 0) ? 2 : 1;          // 2 -> se o grafo possui um ciclo euleriano (grafo euleriano)
}