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
    void topologicalSortUtil(int i, vector<bool>& visited, stack<int>& stack);
    void dfsUtil(int start, vector<bool>& visited);

public:
    Graph(int n); //numerujemy wierzcholki 1...n
    void addEdge(int a, int b);
    void DFS(int start);
    void BFS(int start, bool print);
    void topologicalSort();
    void printGraph();
    bool isCyclic(stack<int> stack);
    ~Graph();
};

#endif //LAB1_GRAPH_H
