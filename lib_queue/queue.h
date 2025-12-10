#pragma once
#include <stdexcept>

//перенести в ветку algorithms в проект Algorithms
template<class T>
class Queue {
	T* _data;
	int _size;
	int _head, _tail;
	int _count;
public:
	Queue();
	Queue(const int size);
	Queue(const Queue& other);
	void push(T val);
	void pop();
	T tail() const;
	bool is_empty() const noexcept;
	bool is_full() const noexcept;
	void clear() noexcept;
	T head() const;
};

template<class T>
Queue<T>::Queue() : _data(nullptr), _size(0), _head(0), _tail(0), _count(0) {}

template<class T>
Queue<T>::Queue(const int size) : _data(new T[size]), _size(size), _head(0), _tail(0),
_count(0) {}

template<class T>
Queue<T>::Queue(const Queue& other) : _data(nullptr), _size(other._size),
_head(other._head), _tail(other._tail), _count(other._count) {
	if (other._data) {
		_data = new T[other._size];;
		for (int i = 0; i < _size; ++i) {
			_data[i] = other._data[i];
		}
	}
}

template<class T>
bool Queue<T>::is_empty() const noexcept {
	return _count == 0;
}

template<class T>
bool Queue<T>::is_full() const noexcept {
	return _count == _size;
}

template<class T> 
void Queue<T>::push(T val) {
	if (is_full()) throw std::logic_error("Error! Queue is full!");
	_data[_tail] = val;
	_tail = (_tail + 1) % _size;
	_count++;
}

template<class T>
void Queue<T>::pop() {
	if (is_empty()) throw std::logic_error("Error! Queue is empty!");
	_head = (_head + 1) % _size;
	_count--;
}

template<class T>
T Queue<T>::tail() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	int index = (_tail - 1 + _size) % _size;
	return _data[index];
}

template<class T>
T Queue<T>::head() const {
	if (is_empty()) throw std::logic_error("Queue is empty!");
	return _data[_head];
}

template<class T>
void Queue<T>::clear() noexcept{
	_head = 0;
	_tail = 0;
	_count = 0;
}


