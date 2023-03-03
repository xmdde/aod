#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <list>
using namespace std;

class Graph {
public:
    int numOfNodes;
    //map<int, bool> visited;
    vector<vector<int>> adj;
    vector <bool> visited;

    Graph(int n) { //mamy n+1 elementow, numerujemy wierzcholki 1...n
        numOfNodes = n;
        adj = *new vector<vector<int>>;
        for (int i = 0; i <= numOfNodes; i++) {
            adj.push_back(*new vector<int>);
            visited.push_back(false);
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
            cout  << "visited: " << visited[i] << '\n';
        }
    }

    void DFS(int start) {
        visited[start] = true; //uwazaj na to
        cout << start << ' ';
        for (int i = 0; i < adj[start].size(); i++) {
            if (!visited[adj[start][i]])
                DFS(adj[start][i]);
        }
    }

    void BFS(int start) {

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
        g.showDegrees();
        g.DFS(1);
        //g.showvisits();
    }
}
