#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits.h>
#include <chrono>
#include "Graph.h"
#include "creator.h"
std::vector<int> dijkstra(Graph *g, int src);

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
        else if (std::string(argv[i]) == "-ss") {
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
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/aod/dijkstra/out/basic/"+resFile, std::ios::out);
    file << "f " << graphFile << ' ' << srcFile << "\ng " << g->numOfNodes << ' ' << g->numOfVertexes << ' ' << g->minWeight << ' ' << g->maxWeight << "\n";
    int len = src.size();

    if (mode == 1) { //ss 
        file << "t ";
        long long t = 0;
        while (!src.empty()) {
            auto begin = std::chrono::high_resolution_clock::now();
            int s = src.front();
            src.pop_front();
            dijkstra(g, s);
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            t += elapsed.count();
        }
        file << t/len;
    }
    else {
        std::vector<int> dist;
        long long d = 0; //sum of distances between pairs from source
        while (!src.empty()) {
            int a = src.front();
            src.pop_front();
            int b = src.front();
            dist = dijkstra(g, a);
            file << "d " << a+1 << ' ' << b+1 << ' ' << dist[b] << '\n';
            d += dist[b];
        }
        file << "avg " << (2*d)/len << "\n";
    }
    file.close();
    return 0;
}

std::vector<int> dijkstra(Graph *g, int src) {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int> >, std::greater<> > priorityQueue;
    std::vector<int> dist(g->numOfNodes, INT_MAX);
    dist[src] = 0;
    priorityQueue.emplace(0, src);

    while (!priorityQueue.empty()){
        int u = priorityQueue.top().second;
        priorityQueue.pop();
        for (auto i : g->adj[u]) {
            int v = i.first;
            int weight = i.second;
            
            //update distance to v if better
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                priorityQueue.emplace(dist[v], v);
            }
        }
    }
    return dist;
}