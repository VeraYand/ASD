#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "../lib_tvector/tvector.h"

template <typename T>
class Heap {
	TVector<T> _data;
	int get_parent(int i) const;
	int get_left(int i) const;
	int get_right(int i) const;
	void sift_up(int index);
	void sift_down(int index);

public:
	Heap();
	Heap(const Heap<T>& other);
	~Heap();
	bool is_empty() const;
	void insert(T value);
	void erase();
	const T& get_root() const;
};

template <typename T>
Heap<T>::Heap() : _data() {
}

template <typename T>
Heap<T>::Heap(const Heap& other) : _data(other._data) {
}

template <typename T>
Heap<T>::~Heap() {
}

template <typename T>
int Heap<T>::get_parent(int i) const { return (i - 1) / 2; }

template <typename T>
int Heap<T>::get_left(int i) const { return 2 * i + 1; }

template <typename T>
int Heap<T>::get_right(int i) const { return 2 * i + 2; }

template <typename T>
void Heap<T>::sift_up(int index) {
	while (index > 0) {
		int parent = get_parent(index);
		if (_data[index] < _data[parent]) {
			std::swap(_data[index], _data[parent]);
			index = parent;
		}
		else {
			break;
		}
	}
}

template <typename T>
void Heap<T>::sift_down(int index) {
	int size = _data.size();
	while (true) {
		int left = get_left(index);
		int right = get_right(index);
		int smallest = index;
		if (left < size && _data[left] < _data[smallest]) {
			smallest = left;
		}
		if (right < size && _data[right] < _data[smallest]) {
			smallest = right;
		}

		if (smallest != index) {
			std::swap(_data[index], _data[smallest]);
			index = smallest;
		}
		else {
			break;
		}
	}
}

template <typename T>
bool Heap<T>::is_empty() const { return _data.is_empty(); }

template <typename T>
void Heap<T>::insert(T value) {
	_data.push_back(value);
	sift_up(_data.size() - 1);
}

template <typename T>
void Heap<T>::erase() {
	if (is_empty()) throw std::logic_error("Heap is empty");

	_data[0] = _data.back();
	_data.pop_back();

	if (!is_empty()) {
		sift_down(0);
	}

}

template <typename T>
const T& Heap<T>::get_root() const{
	return _data[0];
}
	