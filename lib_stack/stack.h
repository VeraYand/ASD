#pragma once

//перенести в ветку algorithms в проект Algorithms
template<class T>
class Stack {
	T* _data;
	size_t _size;
	T _top;
public:
	Stack();
	Stack(const T size);
	Stack(const Stack& other);
	void push(T val);
	void pop();
	T top() const;
	bool is_empty() const noexcept;
	bool is_full() const noexcept;
	void clear() noexcept;

};

template<class T>
Stack<T>::Stack(): _data(nullptr), _size(0), _top(-1) {}

template<class T>
Stack<T>::Stack(const T size): _data(new T[size]), _size(size), _top(-1){}

template<class T>
Stack<T>::Stack(const Stack& other): _data(other._data), _size(other._size), _top(other._top) {}

template<class T>
void Stack<T>::push(T val){
	if (is_full()) throw std::logic_error("Error! Stack is full!");
	_data[++_top] = val;
}

template<class T>
void Stack<T>::pop() {
	if (is_empty()) throw std::logic_error("Error! Stack is empty!");
	--_top;
}

template<class T>
T Stack<T>::top() const{
	return _data[_top];
}

template<class T>
bool Stack<T>::is_empty() const noexcept {
	return(_top == -1);
}

template<class T>
bool Stack<T>::is_full() const noexcept {
	return(_top == _size-1);
}

template<class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}