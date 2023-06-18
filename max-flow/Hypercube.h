#ifndef MAX_FLOW_HYPERCUBE_H
#define MAX_FLOW_HYPERCUBE_H
#include <vector>
#include <iostream>
#include "Edge.h"
#include "utils.h"

class Hypercube {
public:
    int k;
    int v; //num of edges
    std::vector<std::vector<Edge*> > adj;

    explicit Hypercube(int k) {
        this->k = k;
        this->v = pow(2,k);
        this->adj = std::vector<std::vector<Edge*> >(v);
        for (int i = 0; i < v; i++) {
            for (int cur = i + 1; cur < v; cur++) {
                if (isPowerOfTwo(i ^ cur) == 1) {
                    Edge* tmp = new Edge(i, cur, k);
                    tmp->rev = new Edge(cur, i, k);
                    adj[i].push_back(tmp);
                }
            }
        }
    }
    int EdmondsKarp(int s, int t);
    int maxFlow(int s, int t, int&paths);
    void printFlow();
};

#endif //MAX_FLOW_HYPERCUBE_H
