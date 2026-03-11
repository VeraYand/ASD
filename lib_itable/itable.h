#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>


template <class TKey, class TVal>
class ITable {
public:
    virtual ~ITable() = default;
    virtual void insert(const TKey& key, const TVal& value) = 0;
    virtual void erase(const TKey& key) = 0;
    virtual TVal find(const TKey& key) const = 0;

    virtual bool is_empty() const noexcept = 0;

    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;

};
