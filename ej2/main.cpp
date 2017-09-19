#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int);

    void addEdge(int, int, int);

    Graph generateMinimumSpanningTree();

private:
    int nodes;
    vector<vector<int>> matrixOfEdges;
};

Graph::Graph(int nodes) : nodes(nodes) {
    for (int i = 0; i < nodes; ++i) {
        vector<int> row;
        matrixOfEdges.push_back(row);
        for (int j = 0; j < nodes; ++j) {
            matrixOfEdges[i].push_back(0);
        }
    }
}

void Graph::addEdge(int nodeA, int nodeB, int weight) {
    matrixOfEdges[nodeA - 1][nodeB - 1] = weight;
    matrixOfEdges[nodeB - 1][nodeA - 1] = weight;
}


Graph Graph::generateMinimumSpanningTree() {
    //Uses Prims algorithm to find MST
}

int main() {
    cout << "Hello, World!" << endl;
    int numberOfNodes = 1;
    int numberOfEdges;
    vector<Graph> graphs;
    while (numberOfNodes) {
        cin >> numberOfNodes >> numberOfEdges;
        Graph newGraph = Graph(numberOfNodes);
        for (int i = 0; i < numberOfEdges; ++i) {
            int nodeA, nodeB, weight;
            cin >> nodeA >> nodeB >> weight;
            newGraph.addEdge(nodeA, nodeB, weight);
        }
        graphs.push_back(newGraph);
    }

    vector<Graph> msts;
    for (int j = 0; j < graphs.size(); ++j) {
        Graph mst = graphs[j].generateMinimumSpanningTree();
        msts.push_back(mst);
    }


    return 0;
}