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

void Graph::DFS(bool print) {
    vector <bool> visited(numOfNodes + 1, false);
    Graph* dfsTree = new Graph(numOfNodes);
    cout << "DFS: ";
    dfsUtil(1, visited, dfsTree, 0);
    if (print) {
        cout << '\n';
        dfsTree->printGraph();
    }
    cout << '\n';
}

void Graph::dfsUtil(int start, vector<bool>& visited, Graph* dfsTree, int prev) {
    visited[start] = true;
    cout << start << ' ';
    if (prev != 0) {
        dfsTree->addEdge(prev, start);
        dfsTree->addEdge(start, prev);
    }
    for (int i : adj[start]) {
        if (!visited[i])
            dfsUtil(i, visited, dfsTree, start);
    }
}

void Graph::BFS(bool print) {
    vector <bool> visited(numOfNodes + 1, false);
    Graph bfsTree = *new Graph(numOfNodes);
    cout << "BFS: ";
    queue<int> q;
    visited[1] = true;
    q.push(1);

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
        cout << "Graph doesn't have a cycle.\n";
        if (numOfNodes <= 200) {
            cout << "Topological ordering:\n";
            while (!stack.empty()) {
                cout << stack.top() << " ";
                stack.pop();
            }
        }
    } else {
        cout << "Graph has a cycle.\n";
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

Graph Graph::transpose() {
    Graph g = *new Graph(numOfNodes);
    for (int i = 1; i <= numOfNodes; i++) {
        for  (int j : adj[i]) {
            g.addEdge(j, i);
        }
    }
    return g;
}

void Graph::SCCs() {
    vector<vector<int>> SCCs;
    stack<int> stack;
    ::stack<int> topOrder;
    vector <bool> visited(numOfNodes + 1, false);
    iterativeTopologicalSort(topOrder);

    Graph transposed = transpose();
    int index = 0;
    while (!topOrder.empty()) {
        int start = topOrder.top();
        topOrder.pop();
        if (!visited[start]) {
            SCCs.push_back(*new vector<int>);
            transposed.dfsUtilSCCs(start, visited, SCCs, index);
            index++;
        }
    }

    cout << "There are " << index << " SCCs in the graph.\n";
    cout << "Number of nodes in each SCCs:\n";

    for (auto i : SCCs) {
        cout << i.size() << ' ';
        if (numOfNodes <= 200) {
            cout << '(';
            for (int j : i) {
                cout << j << ",";
            }
            cout << ")";
        }
        cout << '\n';
    }
}

void Graph::dfsUtilSCCs(int start, vector<bool>& visited, vector<vector<int>>& SCCs, int index) {
    visited[start] = true;
    SCCs[index].push_back(start);
    for (auto it = adj[start].rbegin(); it != adj[start].rend(); it++) {
        if (!visited[*it]) {
            dfsUtilSCCs(*it, visited, SCCs, index);
        }
    }
}

void Graph::dfsTraversalUtil(int start, vector<bool>& visited, queue<int>& q) {
    stack<int> test;
    test.push(start);

    while (!test.empty()) {
        start = test.top();
        test.pop();
        if (visited[start]) {
            continue;
        }
        visited[start] = true;
        q.push(start);
        for (auto i : adj[start]) {
            if (!visited[i])
                test.push(i);
        }
        //q.push(start);
        /*
        for (auto it = adj[start].rbegin(); it != adj[start].rend(); it++) {
            if (!visited[*it])
                test.push(*it);
        } */
    }
}

void Graph::dfsTraversal(queue<int>& queue) {
    vector<bool> visited(numOfNodes + 1, false);
    for (int i = 1; i <= numOfNodes; i++) {
        if (!visited[i])
            dfsTraversalUtil(i, visited, queue);
    }
}

void Graph::kahnAlgorithm() {
    vector<int> topOrder;
    vector<int> inDegree(numOfNodes + 1, 0);
    for (int u = 0; u <= numOfNodes; u++) {
        for (auto i : adj[u]) {
            inDegree[i]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= numOfNodes; i++) {
        if (inDegree[i] == 0)
            q.push(i);
    }
    int count = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topOrder.push_back(u);
        for (auto i : adj[u]) {
            inDegree[i]--;
            if (inDegree[i] == 0)
                q.push(i);
        }
        count++;
    }
    if (count != numOfNodes) {
        cout << "There is a cycle in the graph.\n";
    } else {
        cout << "Topological ordering: ";
        for (auto i: topOrder)
            cout << i << ' ';
    }
}

void Graph::iterativeTopologicalSort(stack<int>& topOrder) {
    vector<bool> visited(numOfNodes + 1, false);
    stack<pair<bool,int>> dfs;
    for(int i = 1; i <= numOfNodes; i++){
        if(!visited[i]){
            dfs.push(make_pair(false,i));
        }
        while(!dfs.empty()){
            pair<bool,int> node=dfs.top();
            dfs.pop();
            if (node.first) {
                topOrder.push(node.second);
                continue;
            }
            if (visited[node.second]) {
                continue;
            }
            visited[node.second]=true;
            dfs.push(make_pair(true, node.second));
            const auto& newVec=adj[node.second]; //vector of neighbours
            for(const auto son: newVec){
                if(!visited[son]){
                    dfs.push(make_pair(false, son));
                }
            }
        }
    }
}

bool Graph::isBipartite(vector<int>& colors) {
    queue<pair<int, int>> q; //{v , color}

    for (int i = 1; i <= numOfNodes; i++) {
        if (colors[i] == 0) {
            q.push({ i, 1 });
            colors[i] = 1;

            while (!q.empty()) {
                pair<int, int> p = q.front();
                q.pop();
                int v = p.first;
                int c = p.second;

                for (int j : adj[v]) {
                    if (colors[j] == c)
                        return false;

                    if (colors[j] == 0) {
                        colors[j] = c * (-1);
                        q.push({ j, colors[j] });
                    }
                }
            }
        }
    }
    return true;
}

void Graph::bipartiteAns() {
    vector<int> colors(numOfNodes + 1, 0); //colors - -1, 1
    if (!isBipartite(colors)) {
        cout << "Graph is not bipartite.\n";
    }
    else {
        cout << "Graph is bipartite.\n";
        if (numOfNodes <= 200) {
            cout << "Set 1: ";
            for (int i = 1; i <= numOfNodes; i++) {
                if (colors[i] == -1) {
                    cout << i << ' ';
                }
            }
            cout << "\nSet 2: ";
            for (int i = 1; i <= numOfNodes; i++) {
                if (colors[i] == 1) {
                    cout << i << ' ';
                }
            }
            cout << '\n';
        }
    }
}

Graph::~Graph() = default;