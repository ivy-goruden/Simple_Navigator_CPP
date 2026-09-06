#include "Graph/graph.hpp"
#include "Algorithms/graph_algorithms.hpp"
#include <chrono>
using namespace std::chrono;

namespace s21{

    class Client{
        public:
            Client();
            ~Client() = default;
            void printMenu();
            void processSignal(int option);
        private:
            s21::s21_Graph graph;
            bool graphLoaded = false;
            void printRoute(const std::vector<int>& route);
            bool readVertex(const s21::s21_Graph& graph, const std::string& prompt,
                    int& vertex);
            void printMatrix(const std::vector<std::vector<int>>& matrix);
            void printSalesman(s21::TsmResult &result, int vertexCount);

    };

}