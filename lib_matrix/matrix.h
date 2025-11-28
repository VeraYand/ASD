#pragma once

#include <iostream>
#include "../lib_math_vector/math_vector.h"

template <class T>
class Matrix: public MathVector<MathVector<T>>{
	int _M;
	int _N;
public:
	Matrix();
	Matrix(int M, int N);
	Matrix(const Matrix& other);

	Matrix operator + (const Matrix& other) {
		std::cout << "\n Matrix add";
		return Matrix();
	}
	Matrix operator - (const Matrix& other) {
		std::cout << "\n Matrix sub";
		return Matrix();
	}
	Matrix operator * (const Matrix& other) {
		std::cout << "\n Matrix mult";
		return Matrix();
	}
	Matrix operator + (const int& scalar) {
		std::cout << "\n Matrix add a scalar";
		return Matrix();
	}
	Matrix operator - (const int& scalar) {
		std::cout << "\n Matrix sub a scalar";
		return Matrix();
	}
	Matrix operator * (const int& scalar) {
		std::cout << "\n Matrix mult a scalar";
		return Matrix();
	}

	Matrix& operator = (const Matrix& other){
		return *this;
	}

	/*bool operator == (const Matrix& other) const noexcept;
	bool operator != (const Matrix& other) const noexcept;

	bool operator += (const Matrix& other);
	bool operator -= (const Matrix& other);
	bool operator *= (const Matrix& other);


	T& operator [] (size_t index);
	const T& operator [] (size_t index) const;

	friend std::ostream& operator <<<T>(std::ostream& out, const Matrix<T>& obj) {
		std::cout << "\n Matrix output";
	}
	friend std::ostream& operator >><T>(std::ostream& out, const Matrix<T>& obj) {
		std::cout << "\n Matrix input";
	}*/

};
template <class T>
Matrix<T>::Matrix(): _M(1), _N(1) {}

template <class T>
Matrix<T>::Matrix(int M, int N) : _M(M), _N(N) {}

template <class T>
Matrix<T>::Matrix(const Matrix& other) : _M(other._M), _N(other._N) {}

