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

    void insert(const TKey& key, const TVal& value) override {
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
        _rows.insert(pos, { key, value });
    }

    void erase(const TKey& key) override {
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

    TVal find(const TKey& key) const override {
        for (auto it = _rows.cbegin(); it != _rows.cend(); ++it) {
            if ((*it).first == key) {
                return (*it).second;
            }
            if ((*it).first > key) {
                break; 
            }
        }
        throw std::out_of_range("Key not found in table");
    }

    bool is_empty() const noexcept override {
        return _rows.count() == 0;
    }

    void print(std::ostream& out) const override {
        out << "{ ";
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            out << "[" << (*it).first << ": " << (*it).second << "] ";
        }
        out << "}";
    }

    void read(std::istream& in) override {
        TKey k;
        TVal v;
        if (in >> k >> v) {
            insert(k, v);
        }
    }
};