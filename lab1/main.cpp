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
    Graph(int n) { //mamy n+1 elementow, numerujemy wierzcholki 1...n
        numOfNodes = n;
        adj = *new vector<vector<int>>;
        for (int i = 0; i <= numOfNodes; i++) {
            adj.push_back(*new vector<int>);
        }
    }

    void addEdge(int a, int b) {
        adj[a].push_back(b);
    }

    void showDegrees() {
        for(auto x: adj) {
            cout << "outdegree: " << x.size() << '\n';
        }
    }

    void showvisits() {
        for (int i = 0; i < numOfNodes; i++) {
            //cout  << "visited: " << visited[i] << '\n';
        }
    }

    void DFS(int start) {
        vector <bool> visited(numOfNodes + 1, false);
        cout << "DFS: ";
        dfsUtil(start, visited);
        cout << '\n';
    }

    void dfsUtil(int start, vector<bool>& visited) {
        visited[start] = true; //uwazaj na to
        cout << start << ' ';
        for (int i = 0; i < adj[start].size(); i++) {
            if (!visited[adj[start][i]])
                dfsUtil(adj[start][i], visited);
        }
    }

    void BFS(int start) {
        vector <bool> visited(numOfNodes + 1, false);
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
                }
            }
        }
    }

    ~Graph() {
        //cout << "destructor executed \n";
    }
};

int main() {
    ifstream ifs = ifstream("/Users/justynaziemichod/Documents/SEM4/aod/lab1/data.txt", ios_base::in);

    if (ifs.is_open()) {
        int a;
        int b;
        int m;
        ifs >> a >> m;
        Graph g = *new Graph(a);

        while (m > 0) {
            ifs >> a >> b;
            g.addEdge(a, b);
            m--;
        }

        ifs.close();
        g.DFS(2);
        g.BFS(2);
    }
}
