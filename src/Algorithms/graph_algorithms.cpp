#include "graph_algorithms.hpp"

using namespace s21;

std::vector<int> s21_GraphAlgorithms::DepthFirstSearch(s21_Graph& graph, int start_vertex) {
    stack<int> s;
    int curVertex = start_vertex - 1;
    std::map<int, bool> visited;
    std::vector<std::vector<int>> matrix = graph.get_matrix();
    std::vector<int> result;
    result.push_back(curVertex + 1);
    while (static_cast<int>(result.size()) < graph.get_vertex_count()) {
        if (!visited[curVertex]) {
            visited[curVertex] = true;
        }
        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (matrix[curVertex][i] != 0 && !visited[i]) {
                s.push(i + 1);
                visited[i] = true;
            }
        }
        curVertex = s.top() - 1;
        result.push_back(curVertex + 1);
        s.pop();
    }
    return result;
}
std::vector<int> s21_GraphAlgorithms::BreadthFirstSearch(s21_Graph& graph, int start_vertex) {
    std::vector<int> result;
    int curVertex = start_vertex - 1;
    std::map<int, bool> visited;
    std::vector<std::vector<int>> matrix = graph.get_matrix();
    queue<int> q;
    result.push_back(curVertex + 1);
    while (static_cast<int>(result.size()) < graph.get_vertex_count()) {
        if (!visited[curVertex]) {
            visited[curVertex] = true;
        }
        for (int i = 0; i < graph.get_vertex_count(); i++) {
            if (matrix[curVertex][i] != 0 && !visited[i]) {
                q.push(i + 1);
                visited[i] = true;
            }
        }
        curVertex = q.front() - 1;
        result.push_back(curVertex + 1);
        q.pop();
    }
    return result;
}

std::map<int, int> s21_GraphAlgorithms::GetShortestPathBetweenAllVertices(s21_Graph& graph, int start_vertex) {
    std::map<int, int> distances;
    std::vector<std::vector<int>> matrix = graph.get_matrix();
    for (int i = 0; i < graph.get_vertex_count(); i++) {
        distances[i] = __INT_MAX__;
    }
    distances[start_vertex - 1] = 0;
    std::map<int, bool> visited;
    for (int i = 0; i < graph.get_vertex_count(); i++) {
        int minVertex = -1;
        for (int j = 0; j < graph.get_vertex_count(); j++) {
            if (!visited[j] && (minVertex == -1 || distances[j] < distances[minVertex])) {
                minVertex = j;
            }
        }
        if (distances[minVertex] == __INT_MAX__) {
            break;
        }
        visited[minVertex] = true;
        for (int j = 0; j < graph.get_vertex_count(); j++) {
            if (matrix[minVertex][j] > 0) {
                int newDist = distances[minVertex] + matrix[minVertex][j];
                if (newDist < distances[j]) {
                    distances[j] = newDist;
                }
            }
        }
    }
    return distances;
}

int s21_GraphAlgorithms::GetShortestPathBetweenTwoVertices(s21_Graph& graph, int start_vertex, int end_vertex) {
    auto distances = GetShortestPathBetweenAllVertices(graph, start_vertex);
    return distances[end_vertex - 1];
}

struct node {
    int start;
    int end;
    int lenght;

    node(int s, int e, int len) : start(s), end(e), lenght(len) {};

    bool operator<(const node& other) {
        if (other.lenght > lenght) {
            return true;
        }
        return false;
    }
    bool operator>(const node& other) {
        if (other.lenght < lenght) {
            return true;
        }
        return false;
    }
};

std::vector<std::vector<int>> s21_GraphAlgorithms::GetLeastSpanningTree(s21_Graph& graph) {
    std::vector<std::vector<int>> matrix = graph.get_matrix();
    int vertexCount = graph.get_vertex_count();
    std::vector<std::vector<int>> result(vertexCount);
    for (int i = 0; i < vertexCount; i++) {
        result[i] = std::vector<int>(vertexCount, 0);
    }

    std::vector<node> distances;
    std::vector<int> visited;
    int curVertex = 0;
    while (static_cast<int>(visited.size()) < vertexCount && curVertex != -1) {
        visited.push_back(curVertex);
        for (int i = 0; i < vertexCount; i++) {
            if (matrix[curVertex][i] != 0 && std::find(visited.begin(), visited.end(), i) == visited.end()) {
                distances.push_back(node(curVertex, i, matrix[curVertex][i]));
            }
        }
        curVertex = -1;
        std::sort(distances.begin(), distances.end());
        for (node n : distances) {
            if (std::find(visited.begin(), visited.end(), n.end) == visited.end()) {
                curVertex = n.end;
                result[n.start][n.end] = matrix[n.start][n.end];
                break;
            }
        }
    }

    return result;
}

bool s21_GraphAlgorithms::isConnected(s21_Graph& graph) {
    const int vertexCount = graph.get_vertex_count();
    if (vertexCount == 0) {
        return false;
    }

    const auto matrix = graph.get_matrix();
    std::vector<bool> visited(vertexCount, false);
    std::vector<int> pending{0};
    visited[0] = true;

    while (!pending.empty()) {
        const int current = pending.back();
        pending.pop_back();
        for (int next = 0; next < vertexCount; ++next) {
            if (matrix[current][next] != 0 && !visited[next]) {
                visited[next] = true;
                pending.push_back(next);
            }
        }
    }

    return std::all_of(visited.begin(), visited.end(), [](bool value) { return value; });
}

bool s21_GraphAlgorithms::isComplete(s21_Graph& graph) {
    auto matrix = graph.get_matrix();
    int vertNum = graph.get_vertex_count();
    for (int i = 0; i < vertNum; i++) {
        for (int x = 0; x < vertNum; x++) {
            if (matrix[i][x] == 0 && i != x) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> s21_GraphAlgorithms::getShortestPathsMatrix(s21_Graph& graph) {
    const int vertexCount = graph.get_vertex_count();
    std::vector<std::vector<int>> result(vertexCount, std::vector<int>(vertexCount, 0));
    for (int i = 0; i < vertexCount; i++) {
        std::map<int, int> paths = s21_GraphAlgorithms::GetShortestPathBetweenAllVertices(graph, i + 1);
        for (int x = 0; x < vertexCount; x++) {
            result[i][x] = paths[x];
        }
    }
    return result;
}

int getNextNode(const std::vector<double>& neighs, const std::vector<int>& visited) {
    // вершина - вес
    double sum = 0.0;
    int last = visited.back();

    // Функция для проверки, посещена ли вершина
    auto contains = [&](int node) { return std::find(visited.begin(), visited.end(), node) != visited.end(); };

    // Подсчет суммы весов доступных ребер
    for (auto i = 0; i < static_cast<int>(neighs.size()); ++i) {
        int node = i + 1;
        if (node == last || contains(node) || neighs[i] <= 0) {
            continue;
        }
        sum += neighs[i];
    }

    if (sum == 0) {
        return -1;
    }

    // Генерация случайного числа
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, sum);
    double probability = dist(gen);

    // Выбор вершины на основе вероятности
    double edgeValue = 0.0;
    for (auto i = 0; i < static_cast<int>(neighs.size()); ++i) {
        int node = i + 1;
        if (node == last || contains(node) || neighs[i] <= 0) {
            continue;
        }
        edgeValue += neighs[i];
        if (probability < edgeValue) {
            return node;
        }
    }

    return -1;
}

TsmResult s21_GraphAlgorithms::NaiveSalesman(const s21_Graph graph) {
    int vertNum = graph.get_vertex_count();
    int* bestPath = nullptr;
    double minDist = __INT_MAX__;
    auto matrix = graph.get_matrix();

    if (vertNum == 0) {
        return TsmResult{nullptr, 0.0};
    }

    std::vector<int> path(vertNum, 0);
    for (int i = 0; i < vertNum; i++) {
        path[i] = i + 1;
    }
    do {
        int newDist = 0;
        for (int i = 0; i < vertNum - 1; i++) {
            newDist += matrix[path[i] - 1][path[i + 1] - 1];
        }
        newDist += matrix[path.back() - 1][path.front() - 1];
        if (newDist < minDist) {
            minDist = newDist;
            delete[] bestPath;
            bestPath = new int[vertNum + 1];
            std::copy(path.begin(), path.end(), bestPath);
            bestPath[vertNum] = path.front();
        }
    } while (std::next_permutation(path.begin(), path.end()));
    return TsmResult{bestPath, minDist};
}

TsmResult s21_GraphAlgorithms::NearestNeighbourSalesman(const s21_Graph graph) {
    int vertNum = graph.get_vertex_count();
    auto matrix = graph.get_matrix();
    std::vector<int> result;
    int* bestPath = nullptr;
    double minDist = 0;
    if (vertNum == 0) {
        return TsmResult{nullptr, 0.0};
    }
    std::vector<int> path(vertNum, 0);
    for (int i = 0; i < vertNum; i++) {
        path[i] = i + 1;
    }

    // 1. Seed and initialize the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // 2. Define the range [0, size - 1]
    std::uniform_int_distribution<> distr(0, path.size() - 1);

    // 3. Generate the random index and fetch the element
    int currVert = path[distr(gen)] - 1;
    result.push_back(currVert + 1);
    while (result.size() < matrix.size()) {
        int clothestNeigh = -1;
        double minDirToNeigh = __INT_MAX__;
        for (auto neigh = 0; neigh < static_cast<int>(matrix.size()); neigh++) {
            if (matrix[currVert][neigh] != 0 && find(result.begin(), result.end(), neigh + 1) == result.end() &&
                matrix[currVert][neigh] < minDirToNeigh) {
                minDirToNeigh = matrix[currVert][neigh];
                clothestNeigh = neigh;
            }
        }
        if (clothestNeigh == -1) {
            throw std::invalid_argument("Graph is not connected");
            return TsmResult{};
        }
        result.push_back(clothestNeigh + 1);
        currVert = clothestNeigh;
        minDist += minDirToNeigh;
    }
    result.push_back(result.at(0));
    minDist += matrix[result.at(vertNum - 1) - 1][result.at(0) - 1];
    bestPath = new int[result.size()];
    std::copy(result.begin(), result.end(), bestPath);

    return TsmResult{bestPath, minDist};
}

TsmResult s21_GraphAlgorithms::SolveTravelingSalesmanProblem(s21_Graph graph) {
    if (!isConnected(graph)) throw std::invalid_argument("Graph is not connected");

    if (!isComplete(graph)) throw std::invalid_argument("Graph is not complete");

    int vertNum = graph.get_vertex_count();
    std::vector<std::vector<double>> pheromones(vertNum, std::vector<double>(vertNum, 1.0));
    const int ANTS = 10;             // муравьи за раунд
    const int ROUNDS = 10;           // раунды
    const double EVAPORATION = 0.2;  // коэффициэнт испарения
    const double PHEROMONE = 100.0;  // феромоны на ребро при успешном нахождении пути

    std::vector<int> bestPath;
    double minDistance = __INT_MAX__;

    for (int r = 0; r < ROUNDS; r++) {
        std::vector<AntPath> roundPaths;
        for (int a = 0; a < ANTS; a++) {
            AntPath path = AntRun(graph, pheromones);
            roundPaths.push_back(path);
        }
        for (int i = 0; i < vertNum; i++) {
            for (int x = 0; x < vertNum; x++) {
                pheromones[i][x] *= (1.0 - EVAPORATION);
                pheromones[i][x] = std::max(0.1, pheromones[i][x]);
            }
        }
        for (auto ant : roundPaths) {
            if (ant.visited.size() < static_cast<size_t>(vertNum + 1) || ant.length <= 0) continue;
            double delta = PHEROMONE / ant.length;
            for (size_t k = 0; k < (ant.visited).size() - 1; k++) {
                auto u = ant.visited[k] - 1;
                auto v = ant.visited[k + 1] - 1;
                pheromones[u][v] += delta;
            }
            if (ant.length < minDistance) {
                minDistance = ant.length;
                bestPath = ant.visited;
            }
        }
    }
    int* vertices = nullptr;
    if (!bestPath.empty()) {
        vertices = new int[bestPath.size()];
        std::copy(bestPath.begin(), bestPath.end(), vertices);
    }

    return TsmResult{vertices, minDistance};
}

s21_GraphAlgorithms::AntPath s21_GraphAlgorithms::AntRun(const s21_Graph& g,
                                                         const std::vector<std::vector<double>>& pheromones) {
    int n = pheromones.size();

    // Инициализация генератора случайных чисел
    static std::mt19937 gen(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));

    // Создание вектора посещенных вершин
    std::vector<int> visited;
    visited.reserve(n + 1);

    // Выбор случайной стартовой вершины (1..n)
    std::uniform_int_distribution<int> dist(0, n - 1);
    int current = dist(gen) + 1;  // нумерация с 1
    int start = current;
    visited.push_back(current);

    // Основной цикл - пока не посетим все вершины
    while (visited.size() < pheromones.size()) {
        std::vector<double> neighs = pheromones[current - 1];
        int nextNode = getNextNode(neighs, visited);
        if (nextNode == -1) {
            return AntPath{{}, 0.0};
        }
        visited.push_back(nextNode);
        current = nextNode;
    }

    // Возвращаемся в стартовую вершину
    visited.push_back(start);

    // Создаем и возвращаем результат
    AntPath result;
    result.visited = visited;
    result.length = static_cast<double>(s21_GraphAlgorithms::getLenght(g, visited));

    return result;
}

int s21_GraphAlgorithms::getLenght(const s21_Graph& graph, const std::vector<int>& visited) {
    int lenght = 0;
    int vertNum = graph.get_vertex_count();
    auto matrix = graph.get_matrix();
    for (size_t i = 0; i < visited.size() - 1; i++) {
        if (visited[i] < 1 || visited[i] > vertNum || visited[i + 1] < 1 || visited[i + 1] > vertNum) {
            return 0;
        }
        lenght += matrix[visited[i] - 1][visited[i + 1] - 1];
    }
    return lenght;
}