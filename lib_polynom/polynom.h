#pragma once
#include "../lib_list/list.h"
#include "../lib_monom/monom.h"
#include <cmath>
#include <algorithm>

class Polynom {
    List<Monom> _items;

public:
    Polynom();
    Polynom(const Polynom& other);
    Polynom(const Monom& m);
    ~Polynom() = default;

    Polynom& operator=(const Polynom& other);

    Polynom& operator+=(const Monom& m);
    Polynom& operator*=(const Monom& m);
    Polynom& operator-=(const Monom& m);
    Polynom& operator/=(const Monom& m);

    Polynom operator+(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;


    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);

    void add_monom(const Monom& m);
    void sort();
    bool is_sorted() const;
    void remove_zero_monoms();
    std::string to_string() const;

    double calculate(const double* values) const; 
    bool is_zero() const; 
    size_t size() const;
};

