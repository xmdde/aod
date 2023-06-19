#ifndef MAX_MATCHING_EDGE_H
#define MAX_MATCHING_EDGE_H

class Edge {
public:
    int s; //source
    int t; //sink
    int flow;
    int capacity;
    Edge* rev;
    Edge(int source, int sink);
    ~Edge() = default;
};

#endif //MAX_MATCHING_EDGE_H