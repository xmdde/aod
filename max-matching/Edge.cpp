#include "Edge.h"

Edge::Edge(int source, int sink) {
    this->s = source;
    this->t = sink;
    this->capacity = 1;
    this->flow = 0;
}