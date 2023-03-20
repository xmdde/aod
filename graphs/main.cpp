#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include "Graph.h"
void ex1();
void ex2();
void ex3();
Graph generateGraph(const string& path);

int main() {
    //ex2();
    ex3();
    //Graph g = generateGraph("/Users/justynaziemichod/Documents/SEM4/aod/graphs/1/data.txt");
    //g.SCCs();
}

void ex1() {

}

void ex2() {
    for (int i = 1; i <= 6; i++) {
        string suffix = "g2a-" + to_string(i) + ".txt";
        cout << suffix << '\n';
        auto begin = chrono::high_resolution_clock::now();
        string path = "/Users/justynaziemichod/Documents/SEM4/aod/graphs/2/" + suffix;
        Graph g = generateGraph(path);
        g.topologicalSort();
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
        cout << elapsed.count() << " ms \n\n";
    }

    for (int i = 1; i <= 6; i++) {
        string suffix = "g2b-" + to_string(i) + ".txt";
        cout << suffix << '\n';
        auto begin = chrono::high_resolution_clock::now();
        string path = "/Users/justynaziemichod/Documents/SEM4/aod/graphs/2/" + suffix;
        Graph g = generateGraph(path);
        g.topologicalSort();
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
        cout << elapsed.count() << " ms \n\n";
    }
}

void ex3() {
    for (int i = 1; i <= 3; i++) {
        string suffix = "g3-" + to_string(i) + ".txt";
        cout << suffix << '\n';
        auto begin = chrono::high_resolution_clock::now();
        string path = "/Users/justynaziemichod/Documents/SEM4/aod/graphs/3/" + suffix;
        Graph g = generateGraph(path);
        g.SCCs();
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin);
        cout << elapsed.count() << " ms \n\n";
    }
}

Graph generateGraph(const string& path) {
    ifstream ifs = ifstream(path, ios_base::in);
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
        return g;
    }
}