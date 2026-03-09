#pragma once
#include"../lib_tvector/tvector.h"


template <class T>
class MathVector : public TVector<T> {
public:
    MathVector() : TVector<T>() {}
    MathVector(size_t capacity) : TVector<T>(capacity) {}
    MathVector(size_t size, const T* arr) : TVector<T>(size, arr) {}
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}
    MathVector(size_t size, const T& value) : TVector<T>() { 
        for (size_t i = 0; i < size; ++i) {
            this->push_back(value);
        }
    }

    MathVector<T> operator + (const MathVector<T>& other);
    MathVector<T> operator - (const MathVector<T>& other);
    T operator * (const MathVector<T>& other);  
    MathVector<T> operator + (const T& val);    
    MathVector<T> operator - (const T& val);    
    MathVector<T> operator * (const T& val);    
};

template <class T>
MathVector<T> MathVector<T>::operator + (const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("Vectors must have same size for addition");
    }

    MathVector<T> result;//через присваивание
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back((*this)[i] + other[i]);
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator - (const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("Vectors must have same size for subtraction");
    }

    MathVector<T> result;
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back((*this)[i] - other[i]);
    }
    return result;
}

template <class T>
T MathVector<T>::operator * (const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::logic_error("Vectors must have same size for dot product");
    }

    T result = T();
    for (size_t i = 0; i < this->size(); i++) {
        result += (*this)[i] * other[i];
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator + (const T& val) {
    MathVector<T> result;
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back((*this)[i] + val);
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator - (const T& val) {
    MathVector<T> result;
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back((*this)[i] - val);
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator * (const T& val) {
    MathVector<T> result;
    for (size_t i = 0; i < this->size(); i++) {
        result.push_back((*this)[i] * val);
    }
    return result;
}