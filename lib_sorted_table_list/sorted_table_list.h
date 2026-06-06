#pragma once

#include "../lib_itable/itable.h"
#include "../lib_list/list.h" 

template <class TKey, class TVal>
class SortedTableOnList : public ITable<TKey, TVal> {
private:
    List<std::pair<TKey, TVal>> _rows;

public:
    SortedTableOnList() = default;
    ~SortedTableOnList() override = default;

    void insert(const TKey& key, const TVal& value) override;

    void erase(const TKey& key) override;
    const TVal& found(const TKey& key) const override;

    bool is_empty() const noexcept override;

    void print(std::ostream& out) const override;

    void read(std::istream& in) override;
};

template <class TKey, class TVal>
void SortedTableOnList<TKey, TVal>::insert(const TKey& key, const TVal& value) {
    size_t pos = 0;
    for (auto it = _rows.begin(); it != _rows.end(); ++it, ++pos) {
        if ((*it).first == key) {
            (*it).second = value;
            return;
        }
        if ((*it).first > key) {
            break;
        }
    }
    _rows.push_back({ key, value });
}

template <class TKey, class TVal>
void SortedTableOnList<TKey, TVal>::erase(const TKey& key) {
    size_t pos = 0;
    for (auto it = _rows.begin(); it != _rows.end(); ++it, ++pos) {
        if ((*it).first == key) {
            _rows.erase(pos);
            return;
        }
        if ((*it).first > key) {
            break;
        }
    }
    throw std::out_of_range("Key not found in table");
}

template <class TKey, class TVal>
const TVal& SortedTableOnList<TKey, TVal>::found(const TKey& key) const {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            return (*it).second;
        }
        if ((*it).first > key) {
            break;
        }
    }
    throw std::out_of_range("Key not found in table");
}

template <class TKey, class TVal>
bool SortedTableOnList<TKey, TVal>::is_empty() const noexcept {
    return _rows.count() == 0;
}

template <class TKey, class TVal>
void SortedTableOnList<TKey, TVal>::print(std::ostream& out) const {
    out << "{ ";
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        out << "[" << (*it).first << ": " << (*it).second << "] ";
    }
    out << "}";
}

template <class TKey, class TVal>
void SortedTableOnList<TKey, TVal>::read(std::istream& in) {
    TKey k;
    TVal v;
    if (in >> k >> v) {
        insert(k, v);
    }
}