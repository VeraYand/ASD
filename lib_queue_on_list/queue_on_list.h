#pragma once
#include <stdexcept>
#include "../lib_list/list.h"

//перенести в ветку algorithms в проект Algorithms
template<class T>
class Queue {
	List<T> _data;
	size_t _size;
public:
	Queue();
	Queue(const int size);
	Queue(const Queue& other);
	void push(T val);
	void pop();
	T tail() const;
	bool is_empty() const;
	bool is_full() const;
	void clear() noexcept;
	T head() const;
};

template<class T>
Queue<T>::Queue() : _data(), _size(0) {}

template<class T>
Queue<T>::Queue(const int size) : _data(), _size(size) {}

template<class T>
Queue<T>::Queue(const Queue& other) : _data(other._data), _size(other._size) {}

template<class T>
bool Queue<T>::is_empty() const {
	return _data.is_empty();
}

template<class T>
bool Queue<T>::is_full() const {
	return _data.count() == _size;
}

template<class T> 
void Queue<T>::push(T val) {
	if (is_full()) throw std::logic_error("Error! Queue is full!");
	_data.push_back(val);
}

template<class T>
void Queue<T>::pop() {
	if (is_empty()) throw std::logic_error("Error! Queue is empty!");
	_data.pop_front();
}

template<class T>
T Queue<T>::tail() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	return _data.tail()->value;
}

template<class T>
T Queue<T>::head() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	return _data.head()->value;
}

template<class T>
void Queue<T>::clear() noexcept{
	_size = 0;
	while (!is_empty()) {
		_data.pop_front();
	}
}


