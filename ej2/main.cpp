#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct arista {
    int inicio;
    int fin;
    int costo;

    bool operator<(const arista a) const {
        if (costo != a.costo)
            return costo < a.costo;
        if (inicio != a.inicio)
            return inicio < a.inicio;
        return fin < a.fin;
    }
};


class Graph {
    friend class Mst;

public:
    Graph(int nodes, int edges);

    void addEdge(arista edge);

    int getNodes();

    vector<arista> getListOfEdges();

    void generateMst();
    int totalCost;

    vector<pair<int,int>> helperOutputTreeEdges;

    int calculateRoot();

    int getTreeHeight();
    int getRoot();

private:
    int nodes;
    int edges;
    vector<arista> listOfEdges;
    vector<vector<int>> matrixOfEdges;

    int find(int node);

    void uni(int nodeA, int nodeB);

    vector<int> parent;
    vector<int> height;

    vector<vector<int>> mstEdges;

    int startingNode;

    int root;
    vector<int> getDistancesFrom(int node);

    pair<int, int> getMaxDistance(vector<int> distances);

    vector<int> getPath(int fromNode, int toNode);

    int treeHeight;

};

Graph::Graph(int nodes, int edges) : nodes(nodes), edges(edges), matrixOfEdges(nodes, vector<int>(nodes, 0)),
                                     mstEdges(nodes, vector<int>(0)) {}

void Graph::addEdge(arista edge) {
    listOfEdges.push_back(edge);
    matrixOfEdges[edge.inicio - 1][edge.fin - 1] = edge.costo;
}

int Graph::getNodes() {
    return nodes;
}

vector<arista> Graph::getListOfEdges() {
    return listOfEdges;
}


int Graph::find(int node) {
    if (parent[node - 1] != node) {
        parent[node - 1] = find(parent[node - 1]);
    }
    return parent[node - 1];
}

void Graph::uni(int nodeA, int nodeB) {
    nodeA = find(nodeA);
    nodeB = find(nodeB);
    if (height[nodeA - 1] < height[nodeB - 1]) {
        parent[nodeA - 1] = nodeB;
    } else {
        parent[nodeB - 1] = nodeA;
    }
    if (height[nodeA - 1] == height[nodeB - 1]) {
        height[nodeA - 1] = height[nodeA - 1] + 1;
    }
}

void Graph::generateMst() {
    //Usamos el algoritmo de Kruskal para conseguir el Arbol Generador Minimo
    for (int j = 1; j < nodes + 1; ++j) {
        height.push_back(1);
        parent.push_back(j);
    }
    totalCost = 0;
    sort(listOfEdges.begin(), listOfEdges.end()); // ordeno las aristas por peso de menor a mayor O(nlogn)
    for (size_t i = 0; i < listOfEdges.size(); ++i) {
        arista a = listOfEdges[i];
        if (find(a.inicio) != find(a.fin)) {
            mstEdges[a.inicio - 1].push_back(a.fin);
            mstEdges[a.fin - 1].push_back(a.inicio);

            // Esto lo hacemos simplemente para poder hacer output de los ejes facilmente mas adelante.
            helperOutputTreeEdges.push_back(make_pair(a.inicio,a.fin));

            totalCost += a.costo;
            uni(a.inicio, a.fin);
        }
    }
}

int Graph::calculateRoot() {

    //Empezamos por conseguir todas las distancias desde un nodo cualquiera
    startingNode = 1;
    vector<int> distancesAux = getDistancesFrom(startingNode);

    //De todas esas distancias, buscamos la maxima. Devuelve el nodo y la distancia hacia el
    //Este resultara ser la primer hoja del camino mas largo del arbol
    pair<int, int> auxNodeDistance = getMaxDistance(distancesAux);

    //De la primer hoja del arbol, repetimos el procedimiento, buscando todas las distancias
    vector<int> distances = getDistancesFrom(auxNodeDistance.first);

    //Encontramos la segunda hoja y la distancia a ella desde la primera
    //Es decir la distancia del camino mas largo
    pair<int, int> nodeDistance = getMaxDistance(distances);


    
    //Buscamos el camino mas largo en si, desde la primer hoja del camino mas largo a la segunda
    vector<int> longestPath = getPath(auxNodeDistance.first, nodeDistance.first);

    treeHeight = longestPath.size();
    root = longestPath[nodeDistance.second / 2];

    return root;

}


vector<int> Graph::getDistancesFrom(int node) {
    // We perform bfs to obtain a vector of distances from a given node
    vector<int> distances(nodes, -1);
    distances[node - 1] = 0;
    queue<int> bfsQueue;
    bfsQueue.push(node);
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        for (size_t i = 0; i < mstEdges[currentNode - 1].size(); ++i) {
            int neighbourNode = mstEdges[currentNode - 1][i];

            if (distances[neighbourNode - 1] == -1) {
                bfsQueue.push(neighbourNode);
                distances[neighbourNode - 1] = distances[currentNode-1] + 1;
            }
        }
    }

    return distances;
}

pair<int, int> Graph::getMaxDistance(vector<int> distances) {
    //Dado un vector de distancias retorna la maxima y el nodo hacia la cual esta es.
    pair<int, int> maxPair(0, 0);

    for (size_t i = 0; i < distances.size(); ++i) {
        maxPair = distances[i] > maxPair.second ? make_pair((int)i + 1, distances[i]) : maxPair;
    }

    return maxPair;
}

vector<int> Graph::getPath(int fromNode, int toNode) {
    //Funcion que devuelve el camino de fromNode a toNode

    //Initialize vector of previous nodes
    vector<int> previousNode(nodes, -1);
    previousNode[fromNode - 1] = 0;

    //Create BFS Queue
    queue<int> bfsQueue;
    bfsQueue.push(fromNode);
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        for (size_t i = 0; i < mstEdges[currentNode - 1].size(); ++i) {
            int neighbourNode = mstEdges[currentNode - 1][i];

            if (previousNode[neighbourNode - 1] == -1) {
                bfsQueue.push(neighbourNode);
                previousNode[neighbourNode - 1] = currentNode;
            }
        }
    }

    vector<int> path;
    int currentNode = toNode;
    while (currentNode != 0) {
        path.push_back(currentNode);
        currentNode = previousNode[currentNode - 1];
    }

    reverse(path.begin(), path.end());
    return path;

}

int Graph::getRoot() {
    return root;
}

int Graph::getTreeHeight() {
    return treeHeight;
}


int main() {
    int numberOfNodes;
    int numberOfEdges;
    vector<Graph> graphs;
    cin >> numberOfNodes >> numberOfEdges;
    while (numberOfNodes) {
        Graph newGraph = Graph(numberOfNodes, numberOfEdges);
        for (int i = 0; i < numberOfEdges; ++i) {
            arista newEdge{};
            cin >> newEdge.inicio >> newEdge.fin >> newEdge.costo;
            newGraph.addEdge(newEdge);
        }
        graphs.push_back(newGraph);
        cin >> numberOfNodes >> numberOfEdges;
    }

    cerr << "Cantidad de Nodos;Cantidad de Ejes;Tiempo generando Mst;Tiempo calculando raiz;Altura del arbol" << endl;

    //Do the work
    for (auto &graph : graphs) {
        high_resolution_clock::time_point beginGeneratingMst = high_resolution_clock::now();
        graph.generateMst();
        high_resolution_clock::time_point endGeneratingMst = high_resolution_clock::now();

        duration<double> elapsedSecsGeneratingMst = duration_cast<duration<double>>(endGeneratingMst - beginGeneratingMst);

        high_resolution_clock::time_point beginCalculatingRoot = high_resolution_clock::now();
        graph.calculateRoot();
        high_resolution_clock::time_point endCalculatingRoot = high_resolution_clock::now();

        duration<double> elapsedSecsCalculatingRoot = duration_cast<duration<double>>(endCalculatingRoot - beginCalculatingRoot);

        cerr << graph.getNodes() << ';' << graph.getListOfEdges().size() << ';'
             << elapsedSecsGeneratingMst.count() << ';' << elapsedSecsCalculatingRoot.count() << ';'<<graph.getTreeHeight() << endl;
    }


    //Do the logging
    for (auto &graph : graphs) {
        cout << graph.totalCost << " " << graph.getRoot() << " " << graph.helperOutputTreeEdges.size();
        for (auto &helperOutputTreeEdge : graph.helperOutputTreeEdges) {
            cout <<" "<< helperOutputTreeEdge.first << " " << helperOutputTreeEdge.second;
        }
        cout << endl;
    }

    return 0;
}