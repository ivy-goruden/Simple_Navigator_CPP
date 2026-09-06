#include <gtest/gtest.h>

#include <filesystem>  // Requires C++17

#include "../Graph/graph.hpp"

namespace fs = std::filesystem;
TEST(Graph, DefaultConstruction) {
    s21::s21_Graph graph;

    EXPECT_EQ(graph.get_vertex_count(), 0);
    EXPECT_TRUE(graph.get_matrix().empty());
    EXPECT_FALSE(graph.is_digraph());
}

TEST(Graph, ConstructsFromMatrix) {
    const std::vector<std::vector<int>> matrix{{0, 7, 0}, {7, 0, 2}, {0, 2, 0}};
    s21::s21_Graph graph(matrix);

    EXPECT_EQ(graph.get_vertex_count(), 3);
    EXPECT_EQ(graph.get_matrix(), matrix);
    EXPECT_FALSE(graph.is_digraph());
}

TEST(Graph, DetectsDirectedGraph) {
    s21::s21_Graph graph({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}});

    EXPECT_TRUE(graph.is_digraph());
}

TEST(Graph, LoadsGraphFromFile) {
    s21::s21_Graph graph;

    graph.LoadGraphFromFile("files/weightedGraph.txt");

    EXPECT_EQ(graph.get_vertex_count(), 5);
    EXPECT_EQ(graph.get_matrix()[1][3], 1);
    EXPECT_EQ(graph.get_matrix()[2][4], 3);
    EXPECT_FALSE(graph.is_digraph());
}

TEST(Graph, ExportGraphToDot) {
    s21::s21_Graph graph;

    graph.LoadGraphFromFile("files/weightedGraph.txt");
    graph.ExportGraphToDot("weightedGraph.dot");
    fs::path filePath = "dot/weightedGraph.dot";

    EXPECT_TRUE(fs::exists(filePath));
}

TEST(Graph, RejectsNonSquareMatrix) {
    EXPECT_THROW(s21::s21_Graph({{0, 1}, {1}}), std::invalid_argument);
}

TEST(Graph, printMatrix) {
    s21::s21_Graph graph;
    graph.LoadGraphFromFile("files/weightedGraph.txt");
    graph.print_matrix();
    EXPECT_EQ(1, 1);
}
