#include "graph.hpp"

using namespace s21;
s21_Graph::s21_Graph() : vertex_count(0), digraph(false) {

}
s21_Graph::s21_Graph(std::vector<std::vector<int>> m ): matrix(m){
    if (!matrix.empty()) {
        for (const auto& row : matrix) {
            if (row.size() != matrix.size()) {
                throw std::invalid_argument("Matrix is not square!");
            }
        }
    }
    vertex_count = matrix.size();
    if (is_digraph(*this)) {
        digraph = true;
    } else {
        digraph = false;
    }

}

s21_Graph::~s21_Graph() {

}

std::vector<std::vector<int>> s21_Graph::get_matrix() const {
    return matrix;
}

int s21_Graph::get_vertex_count() const{
    return vertex_count;
}

void s21_Graph::LoadGraphFromFile(std::string file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    std::getline(file, line);
    vertex_count = stoi(line);
    for (int i = 0; i < vertex_count; i++) {
        matrix.push_back(std::vector<int>());
    }
    int index = 0;
    while(std::getline(file, line) && index < vertex_count) {
        
        std::stringstream line_buffer(line);
        std::string value;

        while(std::getline(line_buffer, value, ' ') && index < vertex_count) {
            if (value == "" || value == " " || value == "\n") {
                continue; // Skip empty values
            }
            auto weight = std::stoi(value);
            if (weight != static_cast<int>(weight) || weight < 0) {
                throw std::runtime_error("Invalid weight value. Only positive integers are allowed.");
            }
            matrix[index].push_back(weight);
        }
        index++;
    }

    if (is_digraph(*this)) {
        digraph = true;
    } else {
        digraph = false;
    }

}

bool s21_Graph::is_digraph(s21_Graph& graph){
    int vertex_count = graph.get_vertex_count();
    std::vector<std::vector<int>> matrix = graph.get_matrix();
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return true;
            }
        }
    }
    return false;
}

bool s21_Graph::is_digraph() const{
    return digraph;
}

void s21_Graph::ExportGraphToDot(std::string file_name) {
    printf("Exporting graph to DOT format in file: %s\n", file_name.c_str());
    std::ofstream file(dotFilesPath + file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    file << (digraph ? "digraph" : "graph") << " G {\n";
    for (int i = 0; i < vertex_count; i++) {
        for (int j = (digraph ? 0 : i); j < vertex_count; j++) {
                if (matrix[i][j] != 0) {
                    file << "    " << i+1 << (digraph ? " -> " : " -- ") << j+1 << " [label=\"" << matrix[i][j] << "\"];\n";
                }   
            }
    }
    file << "}\n";
    file.close();
}

void s21_Graph::print_matrix() const{
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

}

void s21_Graph::print_matrix(std::vector<std::vector<int>> &matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

}