#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct arista {
    int inicio;
    int fin;
    int costo;

    bool operator<(const arista a) const
    {
        if (costo != a.costo)
            return costo > a.costo;
        if (inicio != a.inicio)
            return inicio > a.inicio;
        return fin > a.fin;
    }
};

struct mst {
    vector<arista>listOfEdges;
    int totalCost;
    int root;

};

class Graph {
public:
    Graph(int numberOfNodes, int numberOfEdges);

    void addEdge(arista newEdge);

    mst generateMinimumSpanningTree();

private:
    int nodes;
    int edges;
    vector<arista> listOfEdges;
    vector<int> parent;
    vector<int> height;

    int find(int node);

    void uni(int nodeA, int nodeB);
};

Graph::Graph(int nodes, int edges) : nodes(nodes),edges(edges) {
    for (int j = 1; j < nodes +1; ++j) {
        height.push_back(1);
        parent.push_back(j);
    }
}

void Graph::addEdge(arista edge) {
    listOfEdges.push_back(edge);
}


int Graph::find(int node){
    if (parent[node -1] != node){
        parent[node-1] = find(parent[node-1]);
    }
    return parent[node -1];
}

void Graph::uni(int nodeA, int nodeB){
    nodeA = find(nodeA);
    nodeB = find(nodeB);
    if (height[nodeA-1]<height[nodeB-1]){
        parent[nodeA-1] = nodeB;
    } else {
        parent[nodeB-1] =nodeA;
    }
    if (height[nodeA-1] == height[nodeB-1]){
        height[nodeA-1] = height[nodeA-1] +1;
    }
}

mst Graph::generateMinimumSpanningTree() {
    //Uses Kruskal algorithm to find MST
    //Assumes the diagonal of the matrix is 0
    mst newMst;
    newMst.totalCost = 0;
    sort(listOfEdges.begin(), listOfEdges.end()); // ordeno las aristas por peso de mayor a menor
    for (int i = 0; i < edges; i++) {
        arista a = listOfEdges[i];
        if (find(a.inicio) != find(a.fin)) {
            newMst.listOfEdges.push_back(a);
            newMst.totalCost += a.costo;
            uni(a.inicio, a.fin);
        }
    }

    return newMst;

}






int main() {
    cout << "Hello, World!" << endl;
    int numberOfNodes;
    int numberOfEdges;
    vector<Graph> graphs;
    cin >> numberOfNodes >> numberOfEdges;
    while (numberOfNodes) {
        Graph newGraph = Graph(numberOfNodes, numberOfEdges);
        for (int i = 0; i < numberOfEdges; ++i) {
            arista newEdge;
            cin >> newEdge.inicio >> newEdge.fin>> newEdge.costo;
            newGraph.addEdge(newEdge);
        }
        graphs.push_back(newGraph);
        cin >> numberOfNodes >> numberOfEdges;
    }

    vector<mst> msts;
    for (int j = 0; j < graphs.size(); ++j) {
        mst newMst = graphs[j].generateMinimumSpanningTree();
        msts.push_back(newMst);
    }


    return 0;
}