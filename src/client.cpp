#include "client.hpp"

namespace s21 {

Client::Client() {
    graph = s21_Graph();
    graphLoaded = false;
}

void Client::printRoute(const std::vector<int>& route) {
    for (int vertex : route) {
        std::cout << vertex << ' ';
    }
    std::cout << '\n';
}

bool Client::readVertex(const s21::s21_Graph& graph, const std::string& prompt, int& vertex) {
    std::cout << prompt;
    if (!(std::cin >> vertex) || vertex < 1 || vertex > graph.get_vertex_count()) {
        std::cout << "Invalid vertex number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void Client::printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}

void Client::printSalesman(s21::TsmResult& result, int vertexCount) {
    std::cout << "Route: ";
    if (result.vertices != nullptr) {
        for (int i = 0; i < vertexCount + 1; ++i) {
            std::cout << result.vertices[i] << ' ';
        }
    }
    std::cout << "\nLength: " << result.distance << '\n';
    delete[] result.vertices;
}

void Client::printMenu() {
    std::cout << "\n1. Load graph from file\n"
              << "2. Breadth-first traversal\n"
              << "3. Depth-first traversal\n"
              << "4. Shortest path between two vertices\n"
              << "5. All-pairs shortest paths\n"
              << "6. Minimum spanning tree\n"
              << "7. Traveling salesman problem\n"
              << "\n"
              << "8. Bonus. Travelling salesman\n"
              << "0. Exit\n"
              << "Select an option: ";
}

void Client::processSignal(int option) {
    try {
        if (option == 1) {
            std::string fileName;
            std::cout << "Enter graph file path: ";
            std::cin >> fileName;
            s21::s21_Graph loadedGraph;
            loadedGraph.LoadGraphFromFile(fileName);
            graph = loadedGraph;
            graphLoaded = true;
            std::cout << "Graph loaded: " << graph.get_vertex_count() << " vertices.\n";
        } else if (option >= 2 && option <= 8 && !graphLoaded) {
            std::cout << "Load a graph first.\n";
        } else if (option == 2 || option == 3) {
            int startVertex;
            if (!readVertex(graph, "Start vertex: ", startVertex)) {
                return;
            }
            std::vector<int> route = option == 2 ? s21::s21_GraphAlgorithms::BreadthFirstSearch(graph, startVertex)
                                                 : s21::s21_GraphAlgorithms::DepthFirstSearch(graph, startVertex);
            printRoute(route);
        } else if (option == 4) {
            int startVertex;
            int endVertex;
            if (!readVertex(graph, "Start vertex: ", startVertex) || !readVertex(graph, "End vertex: ", endVertex)) {
                return;
            }
            int distance = s21::s21_GraphAlgorithms::GetShortestPathBetweenTwoVertices(graph, startVertex, endVertex);
            std::cout << "Shortest path length: " << distance << '\n';
        } else if (option == 5) {
            printMatrix(s21::s21_GraphAlgorithms::getShortestPathsMatrix(graph));
        } else if (option == 6) {
            printMatrix(s21::s21_GraphAlgorithms::GetLeastSpanningTree(graph));
        } else if (option == 7) {
            s21::TsmResult result = s21::s21_GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
            printSalesman(result, graph.get_vertex_count());
        } else if (option == 8) {
            int rounds;
            std::cout << "Enter a number of rounds(better up to 10): ";
            if (!(std::cin >> rounds)) {
                std::cout << "Invalid option.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            printf("Original Salesman:\n");
            auto start = high_resolution_clock::now();
            for (int i = 0; i < rounds; i++) {
                s21::TsmResult result = s21::s21_GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
                printSalesman(result, graph.get_vertex_count());
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            printf("Time: %ld\n\n", duration.count());

            printf("Naive Salesman:\n");
            start = high_resolution_clock::now();
            for (int i = 0; i < rounds; i++) {
                s21::TsmResult result = s21::s21_GraphAlgorithms::NaiveSalesman(graph);
                printSalesman(result, graph.get_vertex_count());
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            printf("Time: %ld\n\n", duration.count());

            printf("Clothest Neighbour:\n");
            start = high_resolution_clock::now();
            for (int i = 0; i < rounds; i++) {
                s21::TsmResult result = s21::s21_GraphAlgorithms::NearestNeighbourSalesman(graph);
                printSalesman(result, graph.get_vertex_count());
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            printf("Time in ms: %ld\n\n", duration.count());

        } else if (option != 0) {
            std::cout << "Unknown option.\n";
        }
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}

}  // namespace s21