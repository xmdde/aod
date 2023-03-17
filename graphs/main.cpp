#include <iostream>
#include <list>
#include "Graph.h"

int main() {
    ifstream ifs = ifstream("/Users/justynaziemichod/Documents/SEM4/aod/graphs/data2/1.txt", ios_base::in);

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
        g.DFS(1);
        g.topologicalSort();
    }
}
