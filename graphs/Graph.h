#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H
#include <iostream>
#include <vector>
#include <list>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

class Graph {
private:
    int numOfNodes;
    vector<vector<int>> adj;

public:
    Graph(int n); //numerujemy wierzcholki 1...n

    void addEdge(int a, int b);

    void DFS(int start);

    void dfsUtil(int start, vector<bool>& visited);

    void BFS(int start, bool print);

    void topologicalSortUtil(int i, vector<bool>& visited, stack<int>& stack);

    void topologicalSort();

    void printGraph();

    ~Graph();
};

#endif //LAB1_GRAPH_H
