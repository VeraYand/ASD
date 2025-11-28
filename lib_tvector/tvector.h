#pragma once

#include <iostream>
#include <stdexcept>

#include <algorithm>
#include <random>
#include <functional>

enum State { empty, busy, deleted };

template <class T>
class TVector {
	T* _data;
	size_t _capacity;
	size_t _size;
	size_t _deleted;
	State* _states;

	static const size_t DEFAULT_CAPACITY = 15;

public:
	TVector(size_t capacity = 0);
	//explicit TVector(size_t size); 
	TVector(size_t size, const T* arr);
	TVector(const TVector<T>& other);
	~TVector();

	inline const T* data()const noexcept;
	inline size_t size() const noexcept;
	inline size_t capacity() const noexcept;
	inline T& front();
	inline T& back();
	inline T* begin() noexcept;
	inline T* end() noexcept;

	inline bool is_empty() const noexcept;

	inline size_t get_real_pos(size_t pos)const;

	inline void push_front(const T& value);
	inline void push_back(const T& value);
	inline void insert(size_t pos, const T& value);

	inline void pop_front();
	inline void pop_back();
	inline void erase(size_t pos);

	inline void emplace(size_t pos, const T& value);

	inline void assign(size_t count, const T& value);
	inline const T& at(size_t pos) const;
	inline T& at(size_t pos);
	inline void clear() noexcept;

	inline void shrink_to_fit();
	inline void reserve(size_t new_capacity);
	inline void resize(size_t new_size, const T& value = T());

	bool operator == (const TVector& other) const noexcept;
	bool operator != (const TVector& other) const noexcept;

	TVector& operator = (const TVector& other);
	T& operator [] (size_t index);
	const T& operator [] (size_t index) const;

	template <class T>
	friend void mixing(TVector<T>& vec);

	template <class T>
	friend void sorting(TVector<T>& vec);

	template <class T>
	friend TVector<size_t> search(const TVector<T>& vec, const T& value);

private:
	inline bool is_full() const noexcept;
	void reallocate();
	inline bool deleted_exceeded() const noexcept;
};

template <class T>
TVector<T>::TVector(size_t capacity)
	: _data(nullptr), _capacity(capacity), _size(0), _deleted(0), _states(nullptr)
{
	if (_capacity > 0) {
		_data = new T[_capacity];
		_states = new State[_capacity];
		for (size_t i = 0; i < _capacity; ++i) {
			_states[i] = empty;
		}
	}
}

template <class T>
TVector<T>::TVector(size_t size, const T* arr)
	: _data(nullptr), _capacity(size + DEFAULT_CAPACITY), _size(size), _deleted(0), _states(nullptr)
{
	if (arr == nullptr && size > 0) {
		throw std::invalid_argument("Null array with non-zero size");
	}

	if (_capacity > 0) {
		_data = new T[_capacity];
		_states = new State[_capacity];
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = arr[i];
			_states[i] = busy;
		}

		for (size_t i = _size; i < _capacity; ++i) {
			_states[i] = empty;
		}
	}
}

template <class T>
TVector<T>::TVector(const TVector<T>& other)
	: _data(nullptr), _capacity(other._capacity), _size(other._size), _deleted(other._deleted), _states(nullptr)
{
	if (_capacity > 0) {
		_data = new T[_capacity];
		_states = new State[_capacity];

		for (size_t i = 0; i < _capacity; ++i) {
			_states[i] = other._states[i];
			if (_states[i] == busy) {
				_data[i] = other._data[i];
			}
		}
	}
}

template <class T>
TVector<T>::~TVector()
{
	delete[] _data;
	delete[] _states;
	_capacity = 0;
	_size = 0;
}

template <class T>
inline const T* TVector<T>::data()const noexcept {
	/*if (_size == 0) { return nullptr; }
	T* result = new T[_size];
	size_t index = 0;
	for (size_t i = 0; i < _capacity; ++i) {
		if (_states[i] == busy) {
			result[index++] = _data[i];
		}
	}
	return result;*/

	return _data;
}

template <class T>
inline size_t TVector<T>::size() const noexcept {
	return _size - _deleted;
}

template <class T>
inline size_t TVector<T>::capacity() const noexcept {
	return _capacity;
}

template <class T>
inline T& TVector<T>::front() {
	if (_size != 0) {
		for (size_t i = 0; i < _size; ++i) {
			if (_states[i] == busy) {
				return _data[i];
			}
		}
	}
	throw std::out_of_range("Vector is empty");
}

template <class T>
inline T& TVector<T>::back() {
	if (_size != 0) {
		for (size_t i = _size; i > 0; --i) {
			if (_states[i - 1] == busy) {
				return _data[i - 1];
			}
		}
	}
	throw std::out_of_range("Vector is empty");
}

template <class T>
inline T* TVector<T>::begin() noexcept {
	if (_size != 0) {
		for (size_t i = 0; i < _size; ++i) {
			if (_states[i] == busy) {
				return &_data[i];
			}
		}
	}
	return nullptr;
}

template <class T>
inline T* TVector<T>::end() noexcept {
	if (_size != 0) {
		for (size_t i = _size; i > 0; --i) {
			if (_states[i - 1] == busy) {
				return &_data[i];
			}
		}
	}
	return nullptr;
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
	return (_size - _deleted) == 0;
}

template <class T>
inline size_t TVector<T>::get_real_pos(size_t pos) const {
	size_t current = 0;
	for (size_t i = 0; i < _size; ++i) {
		if (_states[i] == busy) {
			if (current == pos) {
				return i;
			}
			current++;
		}
	}
	throw std::out_of_range("Index out of range");
}

template <class T>
inline void TVector<T>::push_front(const T& value) {
	insert(0, value);
}

template <class T>
inline void TVector<T>::push_back(const T& value) {
	if (is_full()) {
		reserve(_capacity + DEFAULT_CAPACITY);
	}

	_data[_size] = value;
	_states[_size] = busy;
	_size++;
}

template <class T>
inline void TVector<T>::insert(size_t pos, const T& value) {
	if (pos > size()) {
		throw std::out_of_range("Index out of range");
	}

	if (is_full()) {
		reserve(_capacity + DEFAULT_CAPACITY);
	}
	size_t insert_pos = _size;
	if (pos != size()) {
		insert_pos = get_real_pos(pos);

		for (size_t i = _size; i > insert_pos; --i) {
			_data[i] = _data[i - 1];
			_states[i] = _states[i - 1];
		}
	}
	_data[insert_pos] = value;
	_states[insert_pos] = busy;
	_size++;
}

template <class T>
inline void TVector<T>::pop_front() {
	erase(0);
}

template <class T>
inline void TVector<T>::pop_back() {
	if (is_empty()) {
		throw std::out_of_range("Vector is empty");
	}
	for (size_t i = _size; i > 0; --i) {
		const size_t current = i - 1;
		if (_states[current] == busy) {
			_size--;
			_states[current] = empty;
			return;
		}
		if (_states[current] == deleted) {
			_size--;
			_states[current] = empty;
			_deleted--;
		}
	}

}

template <class T>
inline void TVector<T>::erase(size_t pos) {
	if (pos >= size()) {
		throw std::out_of_range("Index out of range");
	}

	size_t real_pos = get_real_pos(pos);
	_states[real_pos] = deleted;
	_deleted++;

	if (deleted_exceeded()) {
		reallocate();
	}
}

template <class T>
inline void TVector<T>::emplace(size_t pos, const T& value) {
	if (pos >= size()) {
		throw std::out_of_range("Index out of range");
	}
	size_t real_pos = get_real_pos(pos);
	_data[real_pos] = value;
}

template <class T>
inline void TVector<T>::assign(size_t count, const T& value) {
	clear();
	reserve(count + DEFAULT_CAPACITY);
	for (size_t i = 0; i < count; ++i) {
		push_back(value);
	}
}

template <class T>
inline bool TVector<T>::is_full() const noexcept {
	return (_size - _deleted) == _capacity;

}

template <class T>
inline const T& TVector<T>::at(size_t pos) const {
	size_t current = 0;
	for (size_t i = 0; i < _size; ++i) {
		if (_states[i] == busy) {
			if (current == pos) {
				return _data[i];
			}
			current++;
		}
	}
	throw std::out_of_range("Index out of range");
}

template <class T>
inline T& TVector<T>::at(size_t pos) {
	size_t current = 0;
	for (size_t i = 0; i < _size; ++i) {
		if (_states[i] == busy) {
			if (current == pos) {
				return _data[i];
			}
			current++;
		}
	}
	throw std::out_of_range("Index out of range");
}

template <class T>
inline void TVector<T>::clear() noexcept {
	delete[] _data;
	delete[] _states;
	_capacity = DEFAULT_CAPACITY;
	_size = 0;
	_deleted = 0;
	_data = new T[_capacity];
	_states = new State[_capacity];
	for (size_t i = 0; i < _capacity; ++i) {
		_states[i] = empty;
	}
}

template <class T>
inline void TVector<T>::shrink_to_fit() {
	if (_size - _deleted < _capacity) {
		reallocate();
	}
}

template <class T>
inline void TVector<T>::reserve(size_t new_capacity) {
	if (new_capacity <= _capacity) {
		return;
	}

	T* new_data = new T[new_capacity];
	State* new_states = new State[new_capacity];

	size_t new_size = 0;
	for (size_t i = 0; i < _size; ++i) {
		if (_states[i] == busy) {
			new_data[new_size] = _data[i];
			new_states[new_size] = busy;
			new_size++;
		}
	}

	for (size_t i = new_size; i < new_capacity; ++i) {
		new_states[i] = empty;
	}

	delete[] _data;
	delete[] _states;

	_data = new_data;
	_states = new_states;
	_capacity = new_capacity;
	_size = new_size;
	_deleted = 0;
}

template <class T>
inline void TVector<T>::resize(size_t new_size, const T& value) {
	if (new_size < size()) {
		size_t to_remove = size() - new_size;
		for (size_t i = 0; i < to_remove; ++i) {
			pop_back();
		}
	}
	else if (new_size > size()) {
		reserve(new_size + DEFAULT_CAPACITY);
		for (size_t i = size(); i < new_size; ++i) {
			push_back(value);
		}
	}
}


template <class T>
inline bool TVector<T>::operator == (const TVector& other) const noexcept {
	if (size() != other.size()) {
		return false;
	}
	for (size_t i = 0; i < size(); ++i) {
		if (at(i) != other.at(i)) {
			return false;
		}
	}
	return true;
}
template <class T>
inline bool TVector<T>::operator != (const TVector& other) const noexcept {
	return !(*this == other);
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector& other) {
	if (this != &other) {
		delete[] _data;
		delete[] _states;

		_capacity = other._capacity;
		_size = other._size;
		_deleted = other._deleted;

		if (_capacity > 0) {
			_data = new T[_capacity];
			_states = new State[_capacity];

			for (size_t i = 0; i < _capacity; ++i) {
				_states[i] = other._states[i];
				if (_states[i] == busy) {
					_data[i] = other._data[i];
				}
			}
		}
		else {
			_data = nullptr;
			_states = nullptr;
		}
	}
	return *this;
}

template <class T>
inline T& TVector<T>::operator[](size_t index) {
	return at(index);
}

template <class T>
inline const T& TVector<T>::operator[](size_t index) const {
	return at(index);
}

template <class T>
void TVector<T>::reallocate() {
	size_t new_size = _size - _deleted;
	if (new_size == _size) { return; }

	size_t new_capacity = new_size + DEFAULT_CAPACITY;
	T* new_data = new T[new_capacity];
	State* new_states = new State[new_capacity];

	for (size_t i = 0, j = 0; i < _size; ++i) {
		if (_states[i] == busy) {
			new_data[j] = _data[i];
			new_states[j] = busy;
			j++;
		}
	}

	for (size_t i = new_size; i < new_capacity; ++i) {
		new_states[i] = empty;
	}

	delete[] _data;
	delete[] _states;

	_data = new_data;
	_states = new_states;
	_capacity = new_capacity;
	_size = new_size;
	_deleted = 0;
}

template <class T>
bool TVector<T>::deleted_exceeded() const noexcept {
	return _deleted > 0 && (_deleted * 100 / _size) > 10;
}

template <class T>
void mixing(TVector<T>& vec) {
	if (vec.is_empty()) return;

	TVector<size_t> busy_indices;
	for (size_t i = 0; i < vec._size; ++i) {
		if (vec._states[i] == busy) {
			busy_indices.push_back(i);
		}
	}

	std::random_device rd;
	std::mt19937 g(rd());

	for (size_t i = busy_indices.size() - 1; i > 0; --i) {
		std::uniform_int_distribution<size_t> dist(0, i);
		size_t j = dist(g);

		std::swap(vec._data[busy_indices[i]], vec._data[busy_indices[j]]);
	}
}

template <class T>
void quick_sort(TVector<T>& vec, int low, int high) {
	if (low < high) {
		T pivot = vec[high];
		int i = low - 1;

		for (int j = low; j <= high - 1; j++) {
			if (vec[j] <= pivot) {
				i++;
				std::swap(vec[i], vec[j]);
			}
		}
		std::swap(vec[i + 1], vec[high]);

		int pi = i + 1;
		quick_sort(vec, low, pi - 1);
		quick_sort(vec, pi + 1, high);
	}
}

template <class T>
void sorting(TVector<T>& vec) {
	if (vec.is_empty()) return;
	quick_sort(vec, 0, vec.size() - 1);
}

template <class T>
TVector<size_t> search(const TVector<T>& vec, const T& value) {
	TVector<size_t> result;

	size_t logical_index = 0;
	for (size_t i = 0; i < vec._size; ++i) {
		if (vec._states[i] == busy) {
			if (vec._data[i] == value) {
				result.push_back(logical_index);
			}
			logical_index++;
		}
	}

	return result;
}