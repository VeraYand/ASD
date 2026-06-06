#pragma once

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TVal>
class UnsortedTableOnArr : public ITable<TKey, TVal> {
private:
    TVector<std::pair<TKey, TVal>> _rows;
    int find_index(const TKey& key) const;

public:
    UnsortedTableOnArr() = default;
    ~UnsortedTableOnArr() override = default;

    void insert(const TKey& key, const TVal& value) override;

    void erase(const TKey& key) override;

    const TVal& found(const TKey& key) const override;

    bool is_empty() const noexcept override;

    void print(std::ostream& out) const override;

    void read(std::istream& in) override;
};

template <class TKey, class TVal>
int UnsortedTableOnArr<TKey, TVal>::find_index(const TKey& key) const {
    for (size_t i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == key) {
            return i;
        }
    }
    return -1;
}

template <class TKey, class TVal>
void UnsortedTableOnArr<TKey, TVal>::insert(const TKey& key, const TVal& value) {
    int index = find_index(key);
    if (index != -1) {
        _rows[index].second = value;
    }
    else {
        _rows.push_back({ key, value });
    }
}

template <class TKey, class TVal>
void UnsortedTableOnArr<TKey, TVal>::erase(const TKey& key) {
    int index = find_index(key);
    if (index != -1) {
        std::swap(_rows[index], _rows.back());
        _rows.pop_back();
        return;
    }
    throw std::out_of_range("Key not found in table");
}

template <class TKey, class TVal>
const TVal& UnsortedTableOnArr<TKey, TVal>::found(const TKey& key) const{
    int index = find_index(key);
    if (index != -1) {
        return _rows[index].second;
    }
    throw std::out_of_range("Key not found in table");
}

template <class TKey, class TVal>
bool UnsortedTableOnArr<TKey, TVal>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TVal>
void UnsortedTableOnArr<TKey, TVal>::print(std::ostream& out) const {
    out << "{ ";
    for (int i = 0; i < _rows.size(); ++i) {
        out << "[" << _rows[i].first << ": " << _rows[i].second << "] ";
    }
    out << "}";
}

template <class TKey, class TVal>
void UnsortedTableOnArr<TKey, TVal>::read(std::istream& in) {
    TKey k;
    TVal v;
    if (in >> k >> v) {
        insert(k, v);
    }
}