#include "Graph.h"
#include "creator.h"
#include "CircularArray.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits.h>
#include <chrono>
std::vector<int> dial(Graph *g, const int src);
//Graph* parseInput();

int main(int argc, char *argv[]) {
    if (argc < 7) {
        std::cerr << "wrong number of arguments!";
        return -1;
    }
    std::string graphFile;
    std::string srcFile;
    std::string resFile;
    short mode;
    for (int i = 1; i < 7; i++) {
        if (std::string(argv[i]) == "-d") {
            graphFile = std::string(argv[i+1]);
        }
        if (std::string(argv[i]) == "-ss") {
            srcFile = std::string(argv[i+1]);
            mode = 1; //ss - time measure
        }
        else if (std::string(argv[i]) == "-p2p") {
            srcFile = std::string(argv[i+1]);
            mode = 2; //p2p - list of distances
        }
        else if (std::string(argv[i]) == "-oss" || std::string(argv[i]) == "-op2p") {
            resFile = std::string(argv[i+1]);
        }
    }
    Graph *g = generateGraph(graphFile); 
    std::list<int> src = parseSources(srcFile, mode); //tutaj juz sa dobre indeksy
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/aod/dijkstra/out/dial/"+resFile, std::ios_base::out); 
    file << "f " << graphFile << ' ' << srcFile << "\ng " << g->numOfNodes << ' ' << g->numOfVertexes << ' ' << g->minWeight << ' ' << g->maxWeight << "\n";
    int len = src.size();

    if (mode == 1) { //ss
        std::vector<int> dist;
        long long t = 0;
        while (!src.empty()) {
            auto begin = std::chrono::high_resolution_clock::now();
            int s = src.front();
            src.pop_front();
            dist = dial(g, s);
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            t += elapsed.count();
        }
        file << "t " << t/len;
    }
    else {
        std::vector<int> dist;
        long long d = 0; //sum of distances between pairs from source
        while (!src.empty()) {
            int a = src.front();
            src.pop_front();
            int b = src.front();
            dist = dial(g, a);
            file << "d " << a+1 << ' ' << b+1 << ' ' << dist[b] << '\n';
            d += dist[b];
        }
        file << "avg " << (2*d)/len << "\n";
    }
    file.close();
    return 0;
}

std::vector<int> dial(Graph* graph, const int source) {
    std::vector<int> dist(graph->numOfNodes, INT_MAX);
    CircularArray cubes = CircularArray(graph->maxWeight + 1);
    int checked = 0;
    dist[source] = 0;
    cubes.set_element(source, 0);

    while (checked < graph->numOfNodes) {
        for (int i = 0; i < cubes.get_size(); i++) {
            while (!cubes.empty(i)) {
                auto u = cubes.get_element(i);
                cubes.delete_element(i);
                checked++;

                for (auto v : graph->adj[u]) {
                    int alt = dist[u] + v.second;
                    if (dist[v.first] == INT_MAX) {
                        dist[v.first] = alt;
                        cubes.set_element(v.first, alt);
                    } else if (alt < dist[v.first]) {
                        cubes.delete_element(dist[v.first]);
                        dist[v.first] = alt;
                        cubes.set_element(v.first, alt);
                    }
                }
            }
        }
    }
    return dist;
}