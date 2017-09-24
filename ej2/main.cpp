#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <queue>
#include <assert.h>

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
    int nodes;
    vector<int> parent;
    vector<int> height;
    vector<vector<int>>adjacentEdges;
    int totalCost;
    int find(int node);
    void uni(int nodeA, int nodeB);


    vector<int> longestPath;
    vector<int> currentPath;
    vector<int> auxVector;
    int startingNode;
    int maxLength;


    vector<int> getLongestPath();

    int root;
    vector<int> getFurthestNode(int node);

    void tryAdding(int node);

    void updateSolutionIfItsBetter();

    vector<int> getDistancesFrom(int node);

    pair<int, int> getMaxDistance(vector<int> vector);

    vector<int> getPath(int first, int second);
};

Mst::Mst(Graph graph): nodes(graph.nodes),adjacentEdges(graph.nodes, vector<int>(0)){
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
            adjacentEdges[a.fin-1].push_back(a.inicio);

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
    //Signature means: first node, lastNode, path.
    startingNode = 1;
    maxLength =0;
    vector<int> distancesAux = getDistancesFrom(startingNode);
    pair<int, int> auxNodeDistance = getMaxDistance(distancesAux);

    vector<int> distances = getDistancesFrom(auxNodeDistance.first);
    pair<int, int> nodeDistance = getMaxDistance(distances);


    //The longest Path goes from auxNodeDistance.first to nodeDistance.first
    //And its of longitude nodeDistance.second.

    vector<int> longestPath = getPath(auxNodeDistance.first, nodeDistance.second);

}

vector<int> Mst::getDistancesFrom(int node) {
    // We perform bfs to obtain a vector of distances from a given node
    vector<int> distances(nodes, -1);
    distances[node-1] = 0;
    queue bfsQueue;
    bfsQueue.push(node);
    while (!bfsQueue.empty()){
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        for (int i = 0; i < adjacentEdges[currentNode - 1].size(); ++i) {
            int neighbourNode = adjacentEdges[currentNode-1][i];

            if(distances[neighbourNode-1] == -1){
                bfsQueue.push(neighbourNode);
                distances[neighbourNode-1] = distances[currentNode]+1;
            }
        }
    }

    return distances;
}

pair<int, int> Mst::getMaxDistance(vector<int> distances) {
    //Pair, <node, distance>
    pair<int, int> maxPair<0,0>;

    for (int i = 0; i < distances.size(); ++i) {
        maxPair = distances[i] > maxPair.second ? make_pair(i+1, distances[i]) : maxPair;
    }

    return maxPair;
}

vector<int> Mst::getPath(int fromNode, int toNode) {
    vector<int> path;
    path.push_back(fromNode);


    queue bfsQueue;
    bfsQueue.push(fromNode);
    while (!bfsQueue.empty()){
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        for (int i = 0; i < adjacentEdges[currentNode - 1].size(); ++i) {
            int neighbourNode = adjacentEdges[currentNode-1][i];

            if(distances[neighbourNode-1] == -1){
                bfsQueue.push(neighbourNode);
                distances[neighbourNode-1] = distances[currentNode]+1;
            }
        }
    }

    return distances;

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