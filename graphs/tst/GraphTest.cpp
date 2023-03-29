//
// Created by Justyna Ziemichod on 29/03/2023.
//
#include "gtest/gtest.h"
#include "Graph.h"
class GraphTest : public ::testing::Test {
public:
    Graph graph = Graph(3);

};
TEST_F(GraphTest,dfgdfg) {
    graph.BFS(1);
    EXPECT_EQ(1,1);
}