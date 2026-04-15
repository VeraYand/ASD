#pragma once
#include <stdexcept>
#include "../lib_heap/heap.h"

template <typename T>
struct PriorityNode {
    T data;
    int priority;
    int ordinal_num;

    PriorityNode(): data(), priority(0), ordinal_num(0) {}
    PriorityNode(const T& data_, const int priority_, const int ordinal_num_) : 
        data(data_), priority(priority_), ordinal_num(ordinal_num_) {}
    bool operator<(const PriorityNode<T>& other) const {
        if (priority != other.priority) {
            return priority > other.priority;
        }
        return ordinal_num < other.ordinal_num;
    }

};

template <typename T>
class PriorityQueue {
    int _ordinal_num;
    Heap<PriorityNode<T>> _heap;
public:
    PriorityQueue();
    PriorityQueue(const PriorityNode<T>& other);
    ~PriorityQueue();
    void insert(T value, int priority);
    void erase();
    bool is_empty() const; 
    const PriorityNode<T>& top() const;

};

template <typename T>
PriorityQueue<T>::PriorityQueue() : _heap(), _ordinal_num(0) {}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::insert(T data, int priority) {
    PriorityNode<T> node(data, priority, _ordinal_num);
    _heap.insert(node);
    _ordinal_num++;
}

template <typename T>
void PriorityQueue<T>::erase() {
    if (is_empty()) throw std::logic_error("PriorityQueue is empty");
    _heap.erase(); 
}

template <typename T>
bool PriorityQueue<T>::is_empty() const {
    return _heap.is_empty();
}

template <typename T>
const PriorityNode<T>& PriorityQueue<T>::top() const {
    if (is_empty()) throw std::logic_error("PriorityQueue is empty");
    return _heap.get_root();
}