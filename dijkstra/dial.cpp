#include <fstream>
#include "Graph.h"
#include "creator.h"
#include "CircularArray.h"

std::vector<int> dial(Graph *g, const int src);
long long dial2(Graph *g, int source, int target);

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
        //long long dist;
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
        std::cout << t;
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
    CircularArray* buckets = new CircularArray(graph->maxWeight + 1);
    int checked = 0;
    dist[source] = 0;
    buckets->set_element(source, 0); //?

    while (buckets->get_ful_size() != 0) {
        for (int i = 0; i < buckets->get_size(); i++) {
            while (!buckets->empty(i)) {

                auto u = buckets->get_element(i); //?
                buckets->delete_element(i, u);
                checked++;

                for (auto v = graph->adj[u].begin(); v != graph->adj[u].end(); ++v) {
                    int alt = dist[u] + v->second;
                    if (dist[v->first] == INT_MAX) {
                        dist[v->first] = alt;
                        buckets->set_element(v->first, alt);
                    } else if (alt < dist[v->first]) {
                        buckets->delete_element(dist[v->first], v->first);
                        dist[v->first] = alt;
                        buckets->set_element(v->first, alt);
                    }
                }
            }
        }
    }
    delete buckets;
    return dist;
}

long long dial2(Graph *g, int source, int target) {
    int n = g->numOfNodes;
    /*  dist[i].first = distance to ith vertex from src vertex
        dist[i].second = iterator to vertex i in bucket number  */
    std::vector<std::pair<long long, std::list<int>::iterator>> dist(g->numOfNodes + 1);
    
    for (int i = 0; i <= g->numOfNodes; i++) {
        dist[i].first = INT_MAX;
    }
    int W = 0;
    for (unsigned long i = 0; i < g->adj.size(); i++) {
        for (unsigned long j = 0; j < g->adj[i].size(); j++) {
            int cost = g->adj[i][j].second;
            if (cost > W) 
                W = cost;
        }
    }

    auto* buckets = new std::list<int>[W * n + 1];
    buckets[0].push_back(source);
    dist[source].first = 0;

    int index = 0;
    while (true) {
        // Go through buckets until one non-empty is found
        while (buckets[index].empty() && index < W*n) {
            index++;
        }
        // finish if there is no empty one
        if (index == W * n) {
            break;
        }
        // take top node from bucket
        int node = buckets[index].front();
        if (node == target) break;
        buckets[index].pop_front();

        // Process all adjacents of extracted vertex and update their distanced if required
        for (auto edge : g->adj[node]) {
            int neighbour = edge.first;
            int cost = edge.second;
            long long neighbourDistance = dist[neighbour].first;

            // if there is a shorter path to v through u
            long long possibleNewDistance = dist[node].first + cost;
            if (neighbourDistance > possibleNewDistance) {
                // if dv is not INT_MAX then it must be in B[dv] bucket
                if (neighbourDistance != INT_MAX) {
                    buckets[neighbourDistance].erase(dist[neighbour].second);
                }
                // updating the distance
                dist[neighbour].first = possibleNewDistance;
                neighbourDistance  = dist[neighbour].first;

                // pushing vertex v into updated distance's bucket
                buckets[neighbourDistance].push_front(neighbour);
                // storing updated iterator in dist[v].second
                dist[neighbour].second = buckets[neighbourDistance].begin();
            }
        }
    }
    delete[] buckets;
    return dist[target].first;
}