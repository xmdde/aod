#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H
#include <iostream>
#include <list>
#include <vector>

class Graph {
public:
    std::list<std::pair<int, int> > *adj; //adjacency list
    int numOfNodes;
    int maxWeight;
    int minWeight;
    int numOfVertexes;
    
    Graph(int numOfNodes);
    ~Graph();
    void addEdge(int src, int dest, int w);
};

#endif //DIJKSTRA_GRAPH_H