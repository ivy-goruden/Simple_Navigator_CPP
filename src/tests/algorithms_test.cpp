#include <gtest/gtest.h>

#include "../Algorithms/graph_algorithms.hpp"

namespace {

s21::s21_Graph makeWeightedGraph() {
    return s21::s21_Graph({{0, 1, 4, 0}, {1, 0, 2, 5}, {4, 2, 0, 1}, {0, 5, 1, 0}});
}

void releaseResult(s21::TsmResult& result) {
    delete[] result.vertices;
    result.vertices = nullptr;
}

s21::s21_Graph makeSalesmanGraph() {
    return s21::s21_Graph({{0, 2, 3, 4}, {2, 0, 4, 3}, {3, 4, 0, 2}, {4, 3, 2, 0}});
}

void expectClosedRoute(const s21::TsmResult& result, int vertexCount) {
    ASSERT_NE(result.vertices, nullptr);
    ASSERT_EQ(result.vertices[0], result.vertices[vertexCount]);

    std::vector<bool> visited(vertexCount, false);
    for (int i = 0; i < vertexCount; ++i) {
        ASSERT_GE(result.vertices[i], 1);
        ASSERT_LE(result.vertices[i], vertexCount);
        visited[result.vertices[i] - 1] = true;
    }
    EXPECT_TRUE(std::all_of(visited.begin(), visited.end(), [](bool value) { return value; }));
}

}  // namespace

TEST(GraphAlgorithms, BreadthFirstSearch) {
    auto graph = makeWeightedGraph();

    EXPECT_EQ(s21::s21_GraphAlgorithms::BreadthFirstSearch(graph, 1), (std::vector<int>{1, 2, 3, 4}));
}

TEST(GraphAlgorithms, DepthFirstSearch) {
    auto graph = makeWeightedGraph();

    EXPECT_EQ(s21::s21_GraphAlgorithms::DepthFirstSearch(graph, 1), (std::vector<int>{1, 3, 4, 2}));
}

TEST(GraphAlgorithms, ShortestPath) {
    auto graph = makeWeightedGraph();

    EXPECT_EQ(s21::s21_GraphAlgorithms::GetShortestPathBetweenTwoVertices(graph, 1, 4), 4);
}

TEST(GraphAlgorithms, AllPairsShortestPaths) {
    auto graph = makeWeightedGraph();

    EXPECT_EQ(s21::s21_GraphAlgorithms::getShortestPathsMatrix(graph),
              (std::vector<std::vector<int>>{{0, 1, 3, 4}, {1, 0, 2, 3}, {3, 2, 0, 1}, {4, 3, 1, 0}}));
}

TEST(GraphAlgorithms, MinimumSpanningTree) {
    auto graph = makeWeightedGraph();

    EXPECT_EQ(s21::s21_GraphAlgorithms::GetLeastSpanningTree(graph),
              (std::vector<std::vector<int>>{{0, 1, 0, 0}, {0, 0, 2, 0}, {0, 0, 0, 1}, {0, 0, 0, 0}}));
}

TEST(GraphAlgorithms, ConnectivityAndCompleteness) {
    auto graph = makeWeightedGraph();
    s21::s21_Graph disconnected({{0, 1, 0}, {1, 0, 0}, {0, 0, 0}});
    s21::s21_Graph complete({{0, 1, 1}, {1, 0, 1}, {1, 1, 0}});

    EXPECT_TRUE(s21::s21_GraphAlgorithms::isConnected(graph));
    EXPECT_FALSE(s21::s21_GraphAlgorithms::isConnected(disconnected));
    EXPECT_FALSE(s21::s21_GraphAlgorithms::isComplete(graph));
    EXPECT_TRUE(s21::s21_GraphAlgorithms::isComplete(complete));
}

TEST(GraphAlgorithms, SalesmanReturnsClosedRoute) {
    auto graph = makeSalesmanGraph();
    const int vertexCount = graph.get_vertex_count();
    s21::TsmResult result = s21::s21_GraphAlgorithms::SolveTravelingSalesmanProblem(graph);

    ASSERT_NE(result.vertices, nullptr);
    EXPECT_GT(result.distance, 0.0);
    EXPECT_EQ(result.vertices[0], result.vertices[vertexCount]);

    std::vector<bool> visited(vertexCount, false);
    for (int i = 0; i < vertexCount; ++i) {
        ASSERT_GE(result.vertices[i], 1);
        ASSERT_LE(result.vertices[i], vertexCount);
        visited[result.vertices[i] - 1] = true;
    }
    EXPECT_TRUE(std::all_of(visited.begin(), visited.end(), [](bool value) { return value; }));

    releaseResult(result);
}

TEST(GraphAlgorithms, NaiveSalesmanFindsShortestRoute) {
    auto graph = makeSalesmanGraph();
    const int vertexCount = graph.get_vertex_count();
    s21::TsmResult result = s21::s21_GraphAlgorithms::NaiveSalesman(graph);

    expectClosedRoute(result, vertexCount);
    EXPECT_DOUBLE_EQ(result.distance, 10.0);

    releaseResult(result);
}

TEST(GraphAlgorithms, NearestNeighbourSalesmanReturnsValidRoute) {
    auto graph = makeSalesmanGraph();
    const int vertexCount = graph.get_vertex_count();
    s21::TsmResult result = s21::s21_GraphAlgorithms::NearestNeighbourSalesman(graph);

    expectClosedRoute(result, vertexCount);
    EXPECT_DOUBLE_EQ(result.distance, 10.0);

    releaseResult(result);
}
