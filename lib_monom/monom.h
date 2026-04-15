#pragma once

#include <stdexcept>
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

#define VARS_COUNT 3

class Monom {
    double _coeff;
    int _powers[VARS_COUNT];
public:
    Monom(const Monom& other);
    Monom(double coeff = 0.0, const int* powers = nullptr);
    ~Monom() = default;

    bool operator>(const Monom& other) const;
    bool operator<(const Monom& other) const;
    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom& operator*=(double val);
    Monom operator-(const Monom& other) const;
    Monom operator/(const Monom& other) const;
    Monom& operator/=(double val);

    double calculate(const double values[VARS_COUNT]);

    static Monom parse(const std::string& str);
    static std::string read_num(const std::string& str, int& pos);  
    std::string to_string() const;

    double getCoeff() const { return _coeff; }
    const int* getPowers() const { return _powers; }
};

