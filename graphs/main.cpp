#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <list>
#include <queue>
using namespace std;

class Graph {
private:
    int numOfNodes;
    vector<vector<int>> adj;

public:
    Graph(int n) { //numerujemy wierzcholki 1...n
        numOfNodes = n;
        adj = *new vector<vector<int>>;
        for (int i = 0; i <= numOfNodes; i++) {
            adj.push_back(*new vector<int>);
        }
    }

    void addEdge(int a, int b) {
        adj[a].push_back(b);
    }

    void DFS(int start) {
        vector <bool> visited(numOfNodes + 1, false);
        cout << "DFS: ";
        dfsUtil(start, visited);
        cout << '\n';
    }

    void dfsUtil(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << ' ';
        for (int i = 0; i < adj[start].size(); i++) {
            if (!visited[adj[start][i]])
                dfsUtil(adj[start][i], visited);
        }
    }

    void BFS(int start, bool print) {
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
            bfsTree.printGraph();
        }
    }

    void printGraph() {
        for (int i = 1; i <= numOfNodes; i++) {
            cout << i << ": ";
            for (auto a : adj[i]) {
                cout << a << ' ';
            }
            cout << '\n';
        }
    }

    ~Graph() {
        //add proper destructor
    }
};

int main() {
    ifstream ifs = ifstream("/Users/justynaziemichod/Documents/SEM4/aod/lab1/data/data.txt", ios_base::in);

    if (ifs.is_open()) {
        char type;
        int a;
        int b;
        int m;
        ifs >> type;
        ifs >> a >> m;
        Graph g = *new Graph(a);

        while (m > 0) {
            ifs >> a >> b;
            g.addEdge(a, b);
            if (type == 'U') {
                g.addEdge(b, a);
            }
            m--;
        }
        
        ifs.close();
        g.BFS(1, true);
    }
}
