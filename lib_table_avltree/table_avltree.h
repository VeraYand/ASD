#pragma once

#include "../lib_itable/itable.h"
#include "../lib_avltree/avltree.h"

template <class TKey, class TValue>
class TableOnAVLTree : public ITable<TKey, TValue> {
private:
    AVLTree<TKey, TValue> _rows;

public:
    TableOnAVLTree(): _rows(){}
    ~TableOnAVLTree() override = default;

    void insert(const TKey& key, const TValue& value) override;

    void erase(const TKey& key) override;

    const TValue& found(const TKey& key) const override;

    bool is_empty() const noexcept override;

    void print(std::ostream& out) const override;

    void read(std::istream& in) override;
};

template <class TKey, class TValue>
void TableOnAVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_rows.found(key) != nullptr) {
        throw std::logic_error("The key must be unique!");
    }
    _rows.insert(key, value);
}

template <class TKey, class TValue>
void TableOnAVLTree<TKey, TValue>::erase(const TKey& key) {
    if (_rows.found(key) == nullptr) {
        throw std::logic_error("The key not be found!");
    }
    _rows.erase(key);
}

template <class TKey, class TValue>
const TValue& TableOnAVLTree<TKey, TValue>::found(const TKey& key) const {
    TValue* val = _rows.found(key);
    if (!val) {
        throw std::logic_error("The key not be found!");
    }
    return *val;
}

template <class TKey, class TValue>
bool TableOnAVLTree<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void TableOnAVLTree<TKey, TValue>::print(std::ostream& out) const {
    _rows.print(out);
}

template <class TKey, class TValue>
void TableOnAVLTree<TKey, TValue>::read(std::istream& in) {
    TKey k;
    TValue v;
    if (in >> k >> v) {
        _rows.insert(k, v);
    }
}
