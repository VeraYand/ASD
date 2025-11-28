#pragma once

#include "../lib_matrix/matrix.h"
//
//template <class T>
//class TriagleMatrix: public Matrix{
//	int _size;
//
//public:
//	TriagleMatrix();
//	TriagleMatrix(const TriagleMatrix&);
//
//	bool operator == (const TriagleMatrix& other) const noexcept;
//	bool operator != (const TriagleMatrix& other) const noexcept;
//
//	bool operator += (const TriagleMatrix& other) const noexcept;
//	bool operator -= (const TriagleMatrix& other) const noexcept;
//	bool operator *= (const TriagleMatrix& other) const noexcept;
//
//	T& operator [] (size_t index);
//	const T& operator [] (size_t index) const;
//
//	friend std::ostream& operator <<<T>(std::ostream& out, const TriagleMatrix<T>& obj);
//
//};