#include "gtest/gtest.h"
#include "Graph.h"
class GraphTest : public ::testing::Test {
public:
    Graph graph = Graph(3);
};

TEST_F(GraphTest, printTests) {
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(1, 3);
    graph.BFS(1);
    graph.DFS(1);
    //EXPECT_EQ(1,1);
}

TEST_F(GraphTest, dddd) {
    Graph g = Graph(4);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    Graph gTransposed = g.transpose();
    gTransposed.printGraph();
}