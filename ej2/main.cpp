#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

struct arista {
    int inicio;
    int fin;
    int costo;

    bool operator<(const arista a) const
    {
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
    Graph(int numberOfNodes, int numberOfEdges);

    void addEdge(arista newEdge);

    Mst generateMinimumSpanningTree();

private:
    int nodes;
    int edges;
    vector<arista> listOfEdges;
    vector<vector<int>> matrixOfEdges;




};

Graph::Graph(int nodes, int edges) : nodes(nodes),edges(edges), matrixOfEdges(nodes, vector<int>(nodes,0)) {}

void Graph::addEdge(arista edge) {
    listOfEdges.push_back(edge);
    matrixOfEdges[edge.inicio-1][edge.fin-1] = edge.costo;
}


class Mst {
public:
    Mst(Graph graph);
    int getRoot();

private:
    vector<int> parent;
    vector<int> height;
    vector<vector<int>>adjacentEdges;
    int totalCost;
    int find(int node);
    void uni(int nodeA, int nodeB);

    vector<int> getLongestPath();

    tuple<int, int, vector<int>> getFurthestNode(int i);

    int root;
};

Mst::Mst(Graph graph): adjacentEdges(graph.nodes, vector<int>(0)){
    for (int j = 1; j < graph.nodes +1; ++j) {
        height.push_back(1);
        parent.push_back(j);
    }
    totalCost = 0;
    sort(graph.listOfEdges.begin(), graph.listOfEdges.end()); // ordeno las aristas por peso de menor a mayor
    for (int i = 0; i < graph.listOfEdges.size(); i++) {
        arista a = graph.listOfEdges[i];
        if (find(a.inicio) != find(a.fin)) {
            adjacentEdges[a.inicio-1].push_back(a.fin);
            totalCost += a.costo;
            uni(a.inicio, a.fin);
        }
    }
}


int Mst::find(int node){
    if (parent[node -1] != node){
        parent[node-1] = find(parent[node-1]);
    }
    return parent[node -1];
}

void Mst::uni(int nodeA, int nodeB){
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



int Mst::getRoot(){
    vector<int> longestPath = getLongestPath();

    root = longestPath[longestPath.size()/2]; //Check if we need +1


}

vector<int> Mst::getLongestPath() {
    //Signature means: from, to, path.
    tuple<int, int, vector<int>> farawayNode = getFurthestNode(1);
    tuple<int, int, vector<int>> furthestNode  = getFurthestNode(get<1>(farawayNode));

    return vector<int>();
}

tuple<int, int, vector<int>> Mst::getFurthestNode(int from) {
    vector<int> distances(adjacentEdges.size(),0);


    //Since there are no cycles, there are no repetitive calls so theres no use of DP
    //We can do a naive implementation
    for (int i = 0; i < adjacentEdges[from-1].size(); ++i) {

    }


    return tuple<int, int, vector<int>>();
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

    vector<Mst> msts;
    for (int j = 0; j < graphs.size(); ++j) {
        Mst newMst = Mst(graphs[j];
        msts.push_back(newMst);
    }


    return 0;
}