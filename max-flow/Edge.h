#ifndef MAX_FLOW_EDGE_H
#define MAX_FLOW_EDGE_H

#include "utils.h"

class Edge {
public:
    int k;
    int s;  // source
    int t;  // sink
    int flow = 0;
    int capacity;
    Edge* rev;
    Edge(int source, int sink, int k);
    ~Edge() = default;
private:
    void setCapacity();
};

#endif  // MAX_FLOW_EDGE_H
