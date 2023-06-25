#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"

void stats(const int k, const int i) {
    int d = 30;
    long long time = 0;
    long long m = 0;
    for (int it = 0; it < d; it++) {
        auto begin = std::chrono::high_resolution_clock::now();
        Graph g = Graph(k, i);
        int p = -1;
        g.maxMatching(p);
        m += p;
        auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);
        time += t.count();
    }
    std::cout << k << ';' << i << ';' << m/d << ';' << time/d << "\n";
}

void glpkModel(Graph* graph, const int k) {
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/aod/models/model2.txt", std::ios_base::out);
    file << graph->v << '\n';
    file << pow(2, k+1) * graph->i + pow(2, k+1) * 2 << '\n'; //????
    for (int it = 0; it < graph->v; it++) {
        for (auto e : graph->adj[it]) {
            file << e->s << ' ' << e->t << ' ' << e->capacity << '\n';
        }
    }
    file << graph->v - 2 << "\n" << graph->v - 1;
    file.close();
}

int main(int argc, char** argv) {
    int k;
    int i;
    int m = -1;
    if (argc < 5) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    if (std::string(argv[1]) == "-size" && std::string(argv[3]) == "-degree") {
        k = atoi(argv[2]);
        i = atoi(argv[4]);
    } else return 1;

    auto begin = std::chrono::high_resolution_clock::now();
    Graph g = Graph(k, i);
    g.maxMatching(m);
    std::cout << "maximal matching: " << m << "\n";
    auto t = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::high_resolution_clock::now() - begin);
    std::cerr << "t = " << t.count() << " μs\n";

    if ((argc >= 6 && std::string(argv[5]) == "-printMatching") || (argc == 7 && std::string(argv[6]) == "-printMatching"))
        g.printMatching();

    if ((argc >= 6 && std::string(argv[5]) == "-glpk") || (argc == 7 && std::string(argv[6]) == "-glpk"))
        glpkModel(&g, k);
    return 0;
}
