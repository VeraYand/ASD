#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

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
class Graf {
    std::vector<std::list<AdjacentVertex<T>>> adjacency_vec;
    bool is_directed;
    bool is_weighted;   

    int find_vertex_index(const Vertex<T>& v) const {
        for (int i = 0; i < adjacency_vec.size(); i++) {
            if (!adjacency_vec[i].empty() &&
                adjacency_vec[i].front().vertex.value == v.value) {
            }
        }
        return -1;  
    }

public:
    Graf(bool directed = false, bool weighted = false);
    Graf(std::vector<std::pair<std::pair<T, T>, int>> edges,
        bool directed = false, bool weighted = false);
    ~Graf() = default;

    void add_edge(const Edge<T>& edge);
    void add_edge(Vertex<T> v1, Vertex<T> v2, int weight = 1);
    void delete_edge(const Edge<T>& edge);
    void delete_vertex(Vertex<T> v);

    size_t vertex_count() const;
    size_t edge_count() const;
    bool has_edge(const Edge<T>& edge) const;
    bool has_vertex(Vertex<T> v) const;

    bool get_is_directed() const { return is_directed; }
    bool get_is_weighted() const { return is_weighted; }
    const std::vector<std::list<AdjacentVertex<T>>>& get_adjacency_vec() const {
        return adjacency_vec;
    }

};


template<typename T>
Graf<T>::Graf(bool directed, bool weighted)
    : adjacency_vec(), is_directed(directed), is_weighted(weighted) {
}

template<typename T>
Graf<T>::Graf(std::vector<std::pair<std::pair<T, T>, int>> edges,
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
void Graf<T>::add_edge(const Edge<T>& edge) {
    add_edge(edge.first, edge.second, edge.weight);
}

template<typename T>
void Graf<T>::add_edge(Vertex<T> v1, Vertex<T> v2, int weight) {
    if (!is_weighted) {
        weight = 1; 
    }

    int idx1 = static_cast<int>(v1.value);
    int idx2 = static_cast<int>(v2.value);

    int max_idx = std::max(idx1, idx2);

    if (max_idx >= adjacency_vec.size()) {
        adjacency_vec.resize(max_idx + 1);
    }

    auto it1 = std::find_if(adjacency_vec[idx1].begin(),
        adjacency_vec[idx1].end(),
        [&v2](const AdjacentVertex<T>& av) {
            return av.vertex == v2;
        });

    if (it1 == adjacency_vec[idx1].end()) {
        adjacency_vec[idx1].push_back(AdjacentVertex<T>(v2, weight));
    }

    if (!is_directed && idx1 != idx2) {
        auto it2 = std::find_if(adjacency_vec[idx2].begin(),
            adjacency_vec[idx2].end(),
            [&v1](const AdjacentVertex<T>& av) {
                return av.vertex == v1;
            });

        if (it2 == adjacency_vec[idx2].end()) {
            adjacency_vec[idx2].push_back(AdjacentVertex<T>(v1, weight));
        }
    }
}

template<typename T>
void Graf<T>::delete_edge(const Edge<T>& edge) {
    Vertex<T> v1 = edge.first;
    Vertex<T> v2 = edge.second;

    int idx1 = static_cast<int>(v1.value);
    int idx2 = static_cast<int>(v2.value);

    if (idx1 >= adjacency_vec.size() || idx2 >= adjacency_vec.size()) {
        return; 
    }

    adjacency_vec[idx1].remove_if([&v2](const AdjacentVertex<T>& av) {
        return av.vertex == v2;
        });

    if (!is_directed) {
        adjacency_vec[idx2].remove_if([&v1](const AdjacentVertex<T>& av) {
            return av.vertex == v1;
            });
    }
}

template<typename T>
void Graf<T>::delete_vertex(Vertex<T> v) {
    int idx = static_cast<int>(v.value);

    if (idx >= adjacency_vec.size()) {
        return; 
    }

    for (int i = 0; i < adjacency_vec.size(); i++) {
        if (i != idx) {
            adjacency_vec[i].remove_if([&v](const AdjacentVertex<T>& av) {
                return av.vertex == v;
                });
        }
    }

    adjacency_vec[idx].clear();
}

template<typename T>
size_t Graf<T>::vertex_count() const {
    size_t count = 0;
    for (const auto& list : adjacency_vec) {
        if (!list.empty()) {
            count++;
        }
    }
    return count;
}

template<typename T>
size_t Graf<T>::edge_count() const {
    size_t count = 0;
    for (const auto& list : adjacency_vec) {
        count += list.size();
    }

    if (!is_directed) {
        count /= 2; 
    }

    return count;
}

template<typename T>
bool Graf<T>::has_edge(const Edge<T>& edge) const {
    Vertex<T> v1 = edge.first;
    Vertex<T> v2 = edge.second;

    int idx1 = static_cast<int>(v1.value);
    int idx2 = static_cast<int>(v2.value);

    if (idx1 >= adjacency_vec.size() || idx2 >= adjacency_vec.size()) {
        return false;
    }

    auto it = std::find_if(adjacency_vec[idx1].begin(),
        adjacency_vec[idx1].end(),
        [&v2](const AdjacentVertex<T>& av) {
            return av.vertex == v2;
        });

    return it != adjacency_vec[idx1].end();
}

template<typename T>
bool Graf<T>::has_vertex(Vertex<T> v) const {
    int idx = static_cast<int>(v.value);
    return idx < adjacency_vec.size() && !adjacency_vec[idx].empty();
}

