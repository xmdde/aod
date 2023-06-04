#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
#include "creator.h"

Graph* generateGraph(const std::string& path) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    if (!ifs) {
        std::cout << "wrong dir\n";
        exit(1);
    }
    std::string data;
    Graph *g;
    int c = 0;
    while (getline(ifs, data)) {
        c++;
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
        free(line);
    }
    ifs.close();
    return g;
}

Graph* generateGraph2(const std::string& path) {
    std::ifstream ifs = std::ifstream(path, std::ios_base::in);
    std::string data;
    Graph *g;
    std::string c;
    int a;
    int b;
    int n;
    int v; 
    int weight;
    getline(ifs, data);

    ifs >> c;
    ifs >> c >> n >> v;
    g = new Graph(n);
    std::cout << "made graph with " << n << " nodes\n";
    g->numOfVertexes = v;
    std::cout << v << " vertexes\n";

    for (int i = 0; i < 10; i++) {
        ifs >> c;
        ifs >> a >> b >> weight;
        if (weight > g->maxWeight) {
            g->maxWeight = weight;
        }
        g->addEdge(a-1, b-1, weight);
        //std::cout << "edge from " << a << " to " << b << " w: " << weight << "\n";
    }
    ifs.close();
    return g;
}

Graph* buildGraph(const std::string& path) {  
    std::ifstream ifs = std::ifstream(path, std::ios_base::in); 
    std::cout << "ok\n";
    std::string line, sv, se, sh;
    bool e_flag = false;
    bool v_flag = false;
    int spaces = 0;
    int c = 0;
    getline(ifs, line);
    std::cout << "bg\n";
    /*
    while (c < line.length() - 1 and spaces != 1) {
        sh += line[c];
        sh += line[c + 1];
        if (sh == "hi") {
            sh = "";
            int i = c + 3;
            while (spaces != 1) {
                if (line[i] == ' ') {
                    spaces++;
                } else {
                    sh += line[i];
                    i++;
                }
            }
        } else {
            sh = "";
        }
        c++;
    }
    spaces = 0;
    c = 0; */
    getline(ifs, line);
    std::cout << "jkj\n;";
    for (auto _char : line) {
        if (_char == ' ') {
            spaces++;
        } else {
            if (spaces == 2) {
                v_flag = true;
            }
            if (spaces == 3) {
                e_flag = true;
                v_flag = false;
            }
            if (v_flag) {
                sv += _char;
            } else if (e_flag) {
                se += _char;
            }
        }

    }
    auto graph = new Graph(std::stoi(sv));
    c+=2;
    std::string sv1, sv2, cost;
    std::cout << "building\n";
    while (getline(ifs, line)) {
        spaces = 0;
        for (auto _char : line) {
            if (_char == ' ') {
                spaces++;
            } else if (spaces == 1) {
                sv1 += _char;
            } else if (spaces == 2) {
                sv2 += _char;
            } else if (spaces == 3) {
                cost += _char;
            }
        }
        graph->addEdge(std::stoi(sv1), std::stoi(sv2), std::stoi(cost));
        sv1 = "";
        sv2 = "";
        cost = "";
        c++;
    }
    std::cout <<"built\n";
        ifs.close();
    return graph;
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