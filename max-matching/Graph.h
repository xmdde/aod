#ifndef MAX_MATCHING_GRAPH_H
#define MAX_MATCHING_GRAPH_H
#include <vector>
#include "Edge.h"

class Graph {
public:
    int k;
    int v; //num of nodes
    int i; //degree
    std::vector<std::vector<Edge*> > adj;

    explicit Graph(int k, int i) {
        this->k = k;
        this->i = i;
        this->v = pow(2,k+1) + 2;
        this->adj = std::vector<std::vector<Edge*> >(v); //S: v-2, T: v-1
        for (int j = 0; j < pow(2, k); j++) {
            addNeighbors(j);
        }
        linkSourceSink();
    }
    void addNeighbors(int i);
    void linkSourceSink();
    int maxMatching(int& paths);
    int EdmondsKarp(int s, int t);
    void printMatching();
};


#endif //MAX_MATCHING_GRAPH_H
