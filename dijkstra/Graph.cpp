#include "Graph.h"

Graph::Graph(int numOfNodes) {
    this->numOfNodes = numOfNodes;
    this->adj = std::vector< std::vector< std::pair<int,int> > >(numOfNodes);
    for (int i = 0; i < numOfNodes; i++) {
        adj[i] = std::vector<std::pair <int,int> >();
    }
    this->maxWeight = 0; 
    this->minWeight = INT_MAX;
}

void Graph::addEdge(int src, int dest, int w) {
    //this->adj[src].emplace_back(dest, w);
    adj[src].push_back(std::make_pair(dest, w));
    if (w > maxWeight) 
        maxWeight = w;
    else if (w < minWeight)
        minWeight = w;
}

Graph::~Graph() {
}