#pragma once

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TVal>
class SortedTableOnArr : public ITable<TKey, TVal> {
private:
    TVector<std::pair<TKey, TVal>> _rows;
    int lower_bound_index(const TKey& key) const {
        int left = 0;
        int right = _rows.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (_rows[mid].first < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }

public:
    SortedTableOnArr() = default;
    ~SortedTableOnArr() override = default;

    void insert(const TKey& key, const TVal& value) override {
        int pos = lower_bound_index(key);

        if (pos < _rows.size() && _rows[pos].first == key) {
            _rows[pos].second = value;
            return;
        }

        _rows.push_back({ key, value });
        for (int i = _rows.size() - 1; i > pos; --i) {
            std::swap(_rows[i], _rows[i - 1]);
        }
    }

    void erase(const TKey& key) override {
        int pos = lower_bound_index(key);
        if (pos < _rows.size() && _rows[pos].first == key) {
            for (int i = pos; i < _rows.size() - 1; ++i) {
                _rows[i] = _rows[i + 1];
            }
            _rows.pop_back();
            return;
        }
        throw std::out_of_range("Key not found in table");
    }

    TVal find(const TKey& key) const override {
        int pos = lower_bound_index(key);
        if (pos < _rows.size() && _rows[pos].first == key) {
            return _rows[pos].second;
        }
        throw std::out_of_range("Key not found in table");
    }

    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    void print(std::ostream& out) const override {
        out << "{ ";
        for (int i = 0; i < _rows.size(); ++i) {
            out << "[" << _rows[i].first << ": " << _rows[i].second << "] ";
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