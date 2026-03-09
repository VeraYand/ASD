#pragma once
#include <stdexcept>
#include "../lib_list/list.h"

//перенести в ветку algorithms в проект Algorithms
template<class T>
class Stack {
    List<T> _data;
    size_t _size;
public:
    Stack();
    Stack(const size_t size);
    Stack(const Stack& other);
    void push(T val);
    void pop();
    T top() const;
    bool is_empty() const;
    bool is_full() const noexcept;
    void clear() noexcept;

};

template<class T>
Stack<T>::Stack() : _data(), _size(0) {}

template<class T>
Stack<T>::Stack(const size_t size) : _data(), _size(size) {}

template<class T>
Stack<T>::Stack(const Stack& other) : _data(other._data), _size(other._size) {}

template<class T>
void Stack<T>::push(T val) {
    if (is_full()) throw std::logic_error("Error! Stack is full!");
    _data.push_front(val);
}

template<class T>
void Stack<T>::pop() {
    if (is_empty()) throw std::logic_error("Error! Stack is empty!");
    _data.pop_front();
}

template<class T>
T Stack<T>::top() const {
    if (is_empty()) throw std::logic_error("Error! Stack is empty!");
    return _data.head()->value;
}

template<class T>
bool Stack<T>::is_empty() const {
    return(_data.is_empty());
}

template<class T>
bool Stack<T>::is_full() const noexcept {
    return(_data.count() == _size);
}

template<class T>
void Stack<T>::clear() noexcept {
    while (!is_empty()) {
        pop();
    }
}