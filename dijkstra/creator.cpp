#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
#include "creator.h"

Graph* generateGraph(const std::string& path) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    Graph *g;

    while (getline(ifs, data)) {
        char* p;
        char* line = new char[data.length() + 1];
        strcpy(line, data.c_str());
        p = strtok(line, " ");

        if (strcmp(p, "p") == 0) {
            p = strtok(NULL, " ");
            p = strtok(NULL, " ");
            g = new Graph(atoi(p));
            p = strtok(NULL, " ");
            g->numOfVertexes = atoi(p);
        }

        else if (strcmp(p, "a") == 0) {
            p = strtok(NULL, " ");
            int a = atoi(p);
            p = strtok(NULL, " ");
            int b = atoi(p);
            p = strtok(NULL, " ");
            int weight = atoi(p);
            if (weight > g->maxWeight) {
                g->maxWeight = weight;
            }
            g->addEdge(a-1, b-1, weight);
        }
        delete[] line;
    }
    ifs.close();
    return g;
}

std::list<int> parseSources(const std::string& path, short mode) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    std::list<int> src;
    
    while (getline(ifs, data)) {
        char* p;
        char* line = new char[data.length() + 1];
        strcpy(line, data.c_str());
        p = strtok(line, " ");

        if (mode == 1) { //sp
            if (std::string(p) == "s") {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        else if (mode == 2) { //p2p
            if (std::string(p) == "q") {
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
                p = strtok(NULL, " ");
                src.push_back(atoi(p) - 1);
            }
        }
        delete[] line;
    }
    ifs.close();
    return src;
}