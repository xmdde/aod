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
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stack);
    void dfsUtil(int start, vector<bool>& visited, Graph* dfsTree, int prev);
    void dfsUtilSCCs(int start, vector<bool>& visited, vector<vector<int>>& SCCs, int index);

public:
    Graph(int n); //numerujemy wierzcholki 1...n
    ~Graph();
    void addEdge(int a, int b);
    void DFS(bool print);
    void BFS(bool print);
    void topologicalSort();
    void printGraph();
    Graph transpose();
    bool isCyclic(stack<int> stack);
    void SCCs();
    void dfsTraversal(queue<int>& queue);
    void kahnAlgorithm();
    void iterativeTopologicalSort(stack<int>& topOrder);
    bool isBipartite(vector<int>& colors);
    void bipartiteAns();
};

#endif //LAB1_GRAPH_H
