#include "fleury.cpp"

int main(){

    vector<int> grafo[V];

    addEdge(grafo, 0, 1);
    addEdge(grafo, 0, 2);
    addEdge(grafo, 0, 3);
    addEdge(grafo, 3, 4);

    int ret = isEulerian(grafo);
	    if (ret == 0)
	    {
		    cout << "O grafo não é Euleriano" << endl;
            return 0;
        }
	        else if (ret == 1)
            cout << "O grafo é semi-euleriano e possui um caminho de Euler" << endl;
	        
                else
                cout << "O Grafo é Euleriano e possui um circuito de Euler" << endl;

	
    // Procura um vértice com grau ímpar
    int oddDegreeVertex = 0;

    for (int i = 0; i < V; ++i)
    {
        if (grafo[i].size() % 2 != 0)
        {
            oddDegreeVertex = i;
            break;
        }
    }

    cout << "Caminho Euleriano: " << endl;
    eulerCycle(grafo, oddDegreeVertex);
    cout << endl;
    return 0;

}