#ifndef DIJKSTRA_CREATOR_H
#define DIJKSTRA_CREATOR_H
#include "Graph.h"

Graph* generateGraph(const std::string& path);
std::list<int> parseSources(const std::string& path, short mode);

#endif //DIJKSTRA_CREATOR_H