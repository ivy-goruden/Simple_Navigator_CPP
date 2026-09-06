#ifndef S21_GRAPH_H
#define S21_GRAPH_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
namespace s21{
    class s21_Graph{
        private:
            std::vector<std::vector<int>> matrix;
            int vertex_count;
            bool digraph;

            const std::string dotFilesPath = "dot/";
        public:
            s21_Graph();
            s21_Graph(std::vector<std::vector<int>>);
            ~s21_Graph();

            std::vector<std::vector<int>> get_matrix() const;
            int get_vertex_count() const;
            void LoadGraphFromFile(std::string file_name);
            void ExportGraphToDot(std::string file_name);
            void print_matrix() const;
            static void print_matrix(std::vector<std::vector<int>> &matrix);
            bool is_digraph() const;

            static bool is_digraph(s21_Graph& graph);
            inline s21::s21_Graph& operator=(s21::s21_Graph other){
                std::swap(this->matrix, other.matrix);
                std::swap(this->vertex_count, other.vertex_count);
                std::swap(this->digraph, other.digraph);
                return *this;
            }
            s21_Graph(const s21_Graph& other) {
                matrix = other.matrix;
                this->vertex_count = other.vertex_count;
                this->digraph = other.digraph;
            }
    };
}
#endif // S21_GRAPH_H