#include "Graph/graph.hpp"
#include "Algorithms/graph_algorithms.hpp"


int main(){
    s21::s21_Graph graph;
    graph.LoadGraphFromFile("files/CompleteGraph.txt");

    // graph.ExportGraphToDot("spanningTree.dot");
    // auto dfs_result = s21::s21_GraphAlgorithms::DepthFirstSearch(graph, 1);
    // for (auto i: dfs_result) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
    // auto bfs_result = s21::s21_GraphAlgorithms::BreadthFirstSearch(graph, 1);
    // for (auto i: bfs_result) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
    // auto shortest_paths = s21::s21_GraphAlgorithms::GetShortestPathBetweenAllVertices(graph, 1);
    // for (const auto &pair: shortest_paths) {
    //     std::cout << "Vertex: " << pair.first + 1 << ", Distance: " << pair.second << std::endl;
    // }
    // int shortest_path = s21::s21_GraphAlgorithms::GetShortestPathBetweenTwoVertices(graph, 1, 4);
    // std::cout << "Shortest path from vertex 1 to vertex 4: " << shortest_path << std::endl;

    // std::vector<std::vector<int>> result = s21::s21_GraphAlgorithms::GetLeastSpanningTree(graph);
    // s21::s21_Graph::print_matrix(result);
    // s21::s21_Graph treeGraph(result);
    // treeGraph.ExportGraphToDot("treeGraph.dot");
    s21::TsmResult tsmResult =  s21::s21_GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
    printf("%f\n", tsmResult.distance);
    printf("TSM: ");
    for (int i = 0; tsmResult.vertices != nullptr && i < graph.get_vertex_count() + 1; ++i) {
        printf("%d ", tsmResult.vertices[i]);
    }
    printf("\n");
    delete[] tsmResult.vertices;


    return 0;
}
