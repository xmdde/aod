#include "Graph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <queue>
#include <unordered_map>
using namespace std;

Graph::Graph(int n) { //numerujemy wierzcholki 1...n
    numOfNodes = n;
    adj = *new vector<vector<int>>;
    for (int i = 0; i <= numOfNodes; i++) {
        adj.push_back(*new vector<int>);
    }
}

void Graph::addEdge(int a, int b) {
    adj[a].push_back(b);
}

void Graph::DFS(int start) {
    vector <bool> visited(numOfNodes + 1, false);
    cout << "DFS: ";
    dfsUtil(start, visited);
    cout << '\n';
}

void Graph::dfsUtil(int start, vector<bool>& visited) {
    visited[start] = true;
    cout << start << ' ';
    for (int i = 0; i < adj[start].size(); i++) {
        if (!visited[adj[start][i]])
            dfsUtil(adj[start][i], visited);
    }
}

void Graph::BFS(int start, bool print) {
    vector <bool> visited(numOfNodes + 1, false);
    Graph bfsTree = *new Graph(numOfNodes);
    cout << "BFS: ";
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while(!q.empty()) {
        int current = q.front();
        cout << current << ' ';
        q.pop();

        for (int i : adj[current]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
                bfsTree.addEdge(current, i);
                bfsTree.addEdge(i, current);
            }
        }
    }
    cout << '\n';
    if (print) {
        cout << "BFS Tree:\n";
        bfsTree.printGraph();
    }
}

void Graph::topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stack) {
    visited[v] = true;
    for (auto i : adj[v]) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack);
        }
    }
    stack.push(v);
}

void Graph::topologicalSort() {
    vector<bool> visited(numOfNodes + 1, false);
    stack<int> stack;
    for (int i = 1; i <= numOfNodes; i++) {
        if (!visited[i])
            topologicalSortUtil(i, visited, stack);
    }
    if (!isCyclic(stack)) {
        cout << "Graph doesn't have a cycle.\n"; //print sth
        if (numOfNodes <= 200) {
            cout << "Topological ordering:\n";
            while (!stack.empty()) {
                cout << stack.top() << " ";
                stack.pop();
            }
        }
    } else {
        cout << "Graph has a cycle.\n"; //print sth
    }
}

void Graph::printGraph() {
    for (int i = 1; i <= numOfNodes; i++) {
        cout << i << " -> ";
        for (auto a : adj[i]) {
            cout << a << ' ';
        }
        cout << '\n';
    }
}

bool Graph::isCyclic(stack<int> stack) {
    unordered_map<int, int> topologicalPos; //element -> position in topological order
    int i = 0;
    while (!stack.empty()) {
        topologicalPos[stack.top()] = i;
        i++;
        stack.pop();
    }
    for (i = 1; i <= numOfNodes; i++) {
        for (int j : adj[i]) {
            if (topologicalPos[i] > topologicalPos[j])
                return true;
        }
    }
    return false;
}

Graph::~Graph() {
}