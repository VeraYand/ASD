#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "../lib_matrix/matrix.h"

template<typename T>
struct Vertex {
    T value;

    Vertex() : value(T()) {}
    Vertex(T v) : value(v) {}

    bool operator==(const Vertex<T>& other) const {
        return value == other.value;
    }

    bool operator!=(const Vertex<T>& other) const {
        return !(*this == other);
    }
};

template<typename T>
struct Edge {
    Vertex<T> first;
    Vertex<T> second;
    int weight;

    Edge(Vertex<T> v1, Vertex<T> v2, int w = 1)
        : first(v1), second(v2), weight(w) {
    }
};

template<typename T>
struct AdjacentVertex {
    Vertex<T> vertex;
    int weight;

    AdjacentVertex(Vertex<T> v, int w = 1) : vertex(v), weight(w) {}

    bool operator==(const AdjacentVertex<T>& other) const {
        return vertex == other.vertex;
    }
};

template<typename T>
class GraphMatrix {
private:
    Matrix<int> adjacency_matrix;
    bool is_directed;
    bool is_weighted;
    std::vector<T> vertex_values;

    int find_vertex_index(const Vertex<T>& v) const {
        for (size_t i = 0; i < vertex_values.size(); ++i) {
            if (vertex_values[i] == v.value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    GraphMatrix(bool directed = false, bool weighted = false);
    GraphMatrix(std::vector<std::pair<std::pair<T, T>, int>> edges,
        bool directed = false, bool weighted = false);
    ~GraphMatrix() = default;

    void add_edge(const Edge<T>& edge);
    void add_edge(Vertex<T> v1, Vertex<T> v2, int weight = 1);
    void delete_edge(const Edge<T>& edge);
    void delete_vertex(Vertex<T> v);

    size_t vertex_count() const;
    size_t edge_count() const;
    bool has_edge(const Edge<T>& edge) const;
    bool has_vertex(Vertex<T> v) const;
    int get_weight(Vertex<T> v1, Vertex<T> v2) const;

    bool get_is_directed() const { return is_directed; }
    bool get_is_weighted() const { return is_weighted; }
    const Matrix<int>& get_adjacency_matrix() const { return adjacency_matrix; }

    void print() const;
};

template<typename T>
GraphMatrix<T>::GraphMatrix(bool directed, bool weighted)
    : adjacency_matrix(), is_directed(directed), is_weighted(weighted) {
}

template<typename T>
GraphMatrix<T>::GraphMatrix(std::vector<std::pair<std::pair<T, T>, int>> edges,
    bool directed, bool weighted)
    : is_directed(directed), is_weighted(weighted) {
    for (const auto& edge_pair : edges) {
        Vertex<T> v1(edge_pair.first.first);
        Vertex<T> v2(edge_pair.first.second);
        int weight = edge_pair.second;
        add_edge(v1, v2, weight);
    }
}

template<typename T>
void GraphMatrix<T>::add_edge(const Edge<T>& edge) {
    add_edge(edge.first, edge.second, edge.weight);
}

template<typename T>
void GraphMatrix<T>::add_edge(Vertex<T> v1, Vertex<T> v2, int weight) {
    if (!is_weighted) {
        weight = 1;
    }

    int idx1 = find_vertex_index(v1);
    int idx2 = find_vertex_index(v2);

    if (idx1 == -1) {
        idx1 = vertex_values.size();
        vertex_values.push_back(v1.value);

        size_t new_size = vertex_values.size();
        Matrix<int> new_matrix(new_size, new_size, 0);

        for (size_t i = 0; i < new_size - 1; ++i) {
            for (size_t j = 0; j < new_size - 1; ++j) {
                new_matrix[i][j] = adjacency_matrix[i][j];
            }
        }

        adjacency_matrix = new_matrix;
    }

    if (idx2 == -1) {
        idx2 = vertex_values.size();
        vertex_values.push_back(v2.value);

        size_t new_size = vertex_values.size();
        Matrix<int> new_matrix(new_size, new_size, 0);

        for (size_t i = 0; i < new_size - 1; ++i) {
            for (size_t j = 0; j < new_size - 1; ++j) {
                new_matrix[i][j] = adjacency_matrix[i][j];
            }
        }

        adjacency_matrix = new_matrix;
    }

    adjacency_matrix[idx1][idx2] = weight;

    if (!is_directed && idx1 != idx2) {
        adjacency_matrix[idx2][idx1] = weight;
    }
}

template<typename T>
void GraphMatrix<T>::delete_edge(const Edge<T>& edge) {
    Vertex<T> v1 = edge.first;
    Vertex<T> v2 = edge.second;

    int idx1 = find_vertex_index(v1);
    int idx2 = find_vertex_index(v2);

    if (idx1 == -1 || idx2 == -1) {
        return;
    }

    adjacency_matrix[idx1][idx2] = 0;

    if (!is_directed) {
        adjacency_matrix[idx2][idx1] = 0;
    }
}

template<typename T>
void GraphMatrix<T>::delete_vertex(Vertex<T> v) {
    int idx = find_vertex_index(v);

    if (idx == -1) {
        return;
    }

    for (size_t i = 0; i < vertex_values.size(); ++i) {
        adjacency_matrix[idx][i] = 0;
        adjacency_matrix[i][idx] = 0;
    }

    vertex_values[idx] = T(); 
}

template<typename T>
size_t GraphMatrix<T>::vertex_count() const {
    size_t count = 0;
    for (const auto& value : vertex_values) {
        if (value != T()) { 
            count++;
        }
    }
    return count;
}

template<typename T>
size_t GraphMatrix<T>::edge_count() const {
    size_t count = 0;

    for (size_t i = 0; i < adjacency_matrix.rows(); ++i) {
        if (vertex_values[i] == T()) continue;

        for (size_t j = 0; j < adjacency_matrix.cols(); ++j) {
            if (vertex_values[j] == T()) continue;

            if (adjacency_matrix[i][j] != 0) {
                count++;
            }
        }
    }

    if (!is_directed) {
        count /= 2;
    }

    return count;
}

template<typename T>
bool GraphMatrix<T>::has_edge(const Edge<T>& edge) const {
    Vertex<T> v1 = edge.first;
    Vertex<T> v2 = edge.second;

    int idx1 = find_vertex_index(v1);
    int idx2 = find_vertex_index(v2);

    if (idx1 == -1 || idx2 == -1) {
        return false;
    }

    return adjacency_matrix[idx1][idx2] != 0;
}

template<typename T>
bool GraphMatrix<T>::has_vertex(Vertex<T> v) const {
    return find_vertex_index(v) != -1;
}

template<typename T>
int GraphMatrix<T>::get_weight(Vertex<T> v1, Vertex<T> v2) const {
    int idx1 = find_vertex_index(v1);
    int idx2 = find_vertex_index(v2);

    if (idx1 == -1 || idx2 == -1) {
        throw std::invalid_argument("Vertex not found");
    }

    return adjacency_matrix[idx1][idx2];
}

template<typename T>
void GraphMatrix<T>::print() const {
    std::cout << "Adjacency Matrix Graph:" << std::endl;
    std::cout << "Directed: " << (is_directed ? "Yes" : "No") << std::endl;
    std::cout << "Weighted: " << (is_weighted ? "Yes" : "No") << std::endl;
    std::cout << "Vertices: ";
    for (size_t i = 0; i < vertex_values.size(); ++i) {
        if (vertex_values[i] != T()) {
            std::cout << vertex_values[i] << "(" << i << ") ";
        }
    }
    std::cout << std::endl;
    std::cout << "Adjacency Matrix:" << std::endl;
    std::cout << adjacency_matrix << std::endl;
}