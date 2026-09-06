#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H
#include "../Graph/graph.hpp"
#include "../include/s21_queue.h"
#include "../include/s21_stack.h"
#include <map>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <random>
#include <chrono>
namespace s21{
    struct TsmResult {
        int* vertices;    // an array with the route you are looking for (with the vertex traverse order). Instead of int* you can use std::vector<int>
        double distance;  // the length of this route

        TsmResult& operator=(TsmResult other){
            std::swap(this->distance, other.distance);
            std::swap(this->vertices, other.vertices);
            return *this;
        }
    };
    class s21_GraphAlgorithms{
        struct AntPath {
            std::vector<int> visited;
            double length;
        };
        public:
            static std::vector<int> DepthFirstSearch(s21_Graph &graph, int start_vertex);
            static std::vector<int> BreadthFirstSearch(s21_Graph &graph, int start_vertex);
            static std::map<int, int> GetShortestPathBetweenAllVertices(s21_Graph &graph, int start_vertex);
            static int GetShortestPathBetweenTwoVertices(s21_Graph &graph, int start_vertex, int end_vertex);
            static std::vector<std::vector<int>>GetLeastSpanningTree(s21_Graph &graph);
            static TsmResult SolveTravelingSalesmanProblem(s21_Graph graph);
            static TsmResult NaiveSalesman(const s21_Graph graph);
            static TsmResult NearestNeighbourSalesman(const s21_Graph graph);
            static bool isConnected(s21_Graph &graph);
            static bool isComplete(s21_Graph &graph);
            static std::vector<std::vector<int>> getShortestPathsMatrix(s21_Graph& graph);
            static int getLenght(const s21_Graph &graph, const std::vector<int>&visited);
            static AntPath AntRun(const s21_Graph& g, const std::vector<std::vector<double>>& pheromones);
    };
}
#endif // S21_GRAPH_ALGORITHMS_H