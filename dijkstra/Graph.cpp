#include "Graph.h"

Graph::Graph(int numOfNodes) {
    this->numOfNodes = numOfNodes;
    this->adj = new std::list< std::pair<int,int> >[numOfNodes];
    this->maxWeight = 0; 
    this->minWeight = INT_MAX;
}

void Graph::addEdge(int src, int dest, int w) {
    this->adj[src].emplace_back(dest, w);
    if (w > maxWeight) 
        maxWeight = w;
    else if (w < minWeight)
        minWeight = w;
    //this->adj[dest].emplace_back(src, w);
}

Graph::~Graph() {
    delete adj;
}