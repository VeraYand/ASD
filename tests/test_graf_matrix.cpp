#include <gtest/gtest.h>
#include "../lib_graf_matrix/graf_matrix.h"


TEST(MatrixGraphTest, DefaultConstructor) {
    GraphMatrix<int> graph;
    EXPECT_FALSE(graph.get_is_directed());
    EXPECT_FALSE(graph.get_is_weighted());
    EXPECT_EQ(graph.vertex_count(), 0);
    EXPECT_EQ(graph.edge_count(), 0);
}

TEST(MatrixGraphTest, ConstructorWithFlags) {
    GraphMatrix<int> directed_graph(true, false);
    EXPECT_TRUE(directed_graph.get_is_directed());
    EXPECT_FALSE(directed_graph.get_is_weighted());

    GraphMatrix<int> weighted_graph(false, true);
    EXPECT_FALSE(weighted_graph.get_is_directed());
    EXPECT_TRUE(weighted_graph.get_is_weighted());

    GraphMatrix<int> directed_weighted_graph(true, true);
    EXPECT_TRUE(directed_weighted_graph.get_is_directed());
    EXPECT_TRUE(directed_weighted_graph.get_is_weighted());
}

TEST(MatrixGraphTest, AddEdgeUndirectedUnweighted) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    EXPECT_EQ(graph.vertex_count(), 2);
    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1))));
    EXPECT_EQ(graph.get_weight(Vertex<int>(1), Vertex<int>(2)), 1);
}

TEST(MatrixGraphTest, AddEdgeDirectedUnweighted) {
    GraphMatrix<int> graph(true, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    EXPECT_EQ(graph.vertex_count(), 2);
    EXPECT_EQ(graph.edge_count(), 1);
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1))));
}

TEST(MatrixGraphTest, AddEdgeWeighted) {
    GraphMatrix<int> graph(false, true);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2), 10);

    EXPECT_EQ(graph.get_weight(Vertex<int>(1), Vertex<int>(2)), 10);
    EXPECT_EQ(graph.get_weight(Vertex<int>(2), Vertex<int>(1)), 10);
}

TEST(MatrixGraphTest, AddEdgeAutoAddsVertices) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(5), Vertex<int>(10));

    EXPECT_TRUE(graph.has_vertex(Vertex<int>(5)));
    EXPECT_TRUE(graph.has_vertex(Vertex<int>(10)));
    EXPECT_EQ(graph.vertex_count(), 2);
}


TEST(MatrixGraphTest, AddDuplicateEdge) {
    GraphMatrix<int> graph(false, true);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2), 5);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2), 10);

    EXPECT_EQ(graph.get_weight(Vertex<int>(1), Vertex<int>(2)), 10);
    EXPECT_EQ(graph.edge_count(), 1);
}


TEST(MatrixGraphTest, DeleteEdge) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));

    graph.delete_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2)));

    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1))));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(3))));
    EXPECT_EQ(graph.edge_count(), 1);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1))));
}

TEST(MatrixGraphTest, DeleteEdgeDirected) {
    GraphMatrix<int> graph(true, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    graph.delete_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2)));

    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_EQ(graph.edge_count(), 0);
}

TEST(MatrixGraphTest, DeleteVertex) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));
    graph.add_edge(Vertex<int>(1), Vertex<int>(3));

    graph.delete_vertex(Vertex<int>(1));

    EXPECT_FALSE(graph.has_vertex(Vertex<int>(1)));
    EXPECT_TRUE(graph.has_vertex(Vertex<int>(2)));
    EXPECT_TRUE(graph.has_vertex(Vertex<int>(3)));
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(3))));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(3))));
}

TEST(MatrixGraphTest, DeleteVertexUpdatesEdgeCount) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));
    graph.add_edge(Vertex<int>(1), Vertex<int>(3));

    EXPECT_EQ(graph.edge_count(), 3);

    graph.delete_vertex(Vertex<int>(1));

    EXPECT_EQ(graph.edge_count(), 1);
}

TEST(MatrixGraphTest, DeleteVertexRemovesAllEdges) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(1), Vertex<int>(3));
    graph.add_edge(Vertex<int>(1), Vertex<int>(4));

    graph.delete_vertex(Vertex<int>(1));

    EXPECT_EQ(graph.edge_count(), 0);
}


TEST(MatrixGraphTest, HasVertex) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    EXPECT_TRUE(graph.has_vertex(Vertex<int>(1)));
    EXPECT_TRUE(graph.has_vertex(Vertex<int>(2)));
    EXPECT_FALSE(graph.has_vertex(Vertex<int>(3)));
}

TEST(MatrixGraphTest, HasEdge) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1)))); 
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(3))));
}

TEST(MatrixGraphTest, HasEdgeDirected) {
    GraphMatrix<int> graph(true, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));

    EXPECT_TRUE(graph.has_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2))));
    EXPECT_FALSE(graph.has_edge(Edge<int>(Vertex<int>(2), Vertex<int>(1))));
}

TEST(MatrixGraphTest, VertexCount) {
    GraphMatrix<int> graph(false, false);
    EXPECT_EQ(graph.vertex_count(), 0);

    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    EXPECT_EQ(graph.vertex_count(), 2);

    graph.add_edge(Vertex<int>(2), Vertex<int>(3));
    EXPECT_EQ(graph.vertex_count(), 3);
}

TEST(MatrixGraphTest, EdgeCountUndirectedUnweighted) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));
    graph.add_edge(Vertex<int>(3), Vertex<int>(1));

    EXPECT_EQ(graph.edge_count(), 3);
}

TEST(MatrixGraphTest, EdgeCountDirected) {
    GraphMatrix<int> graph(true, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));

    EXPECT_EQ(graph.edge_count(), 2);
}

TEST(MatrixGraphTest, EdgeCountAfterDeletion) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2));
    graph.add_edge(Vertex<int>(2), Vertex<int>(3));

    graph.delete_edge(Edge<int>(Vertex<int>(1), Vertex<int>(2)));
    EXPECT_EQ(graph.edge_count(), 1);
}

TEST(MatrixGraphTest, GetWeight) {
    GraphMatrix<int> graph(false, true);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2), 42);

    EXPECT_EQ(graph.get_weight(Vertex<int>(1), Vertex<int>(2)), 42);
    EXPECT_EQ(graph.get_weight(Vertex<int>(2), Vertex<int>(1)), 42);
}

TEST(MatrixGraphTest, UnweightedGraphIgnoresWeight) {
    GraphMatrix<int> graph(false, false);
    graph.add_edge(Vertex<int>(1), Vertex<int>(2), 99); 

    EXPECT_EQ(graph.get_weight(Vertex<int>(1), Vertex<int>(2)), 1);
}

