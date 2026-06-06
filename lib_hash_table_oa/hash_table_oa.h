#pragma once

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"


#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>

static bool is_prime(size_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

template <class TValue>
struct HashData {
    State _state;
    std::string _key;
    TValue _value;

    HashData() : _state(empty), _key(""), _value() {}
    HashData(const std::string& key, const TValue& val, State st = busy)
        : _state(st), _key(key), _value(val) {
    }
};

template <class TValue>
class HashTableOA : public ITable<std::string, TValue> {
private:
    TVector<HashData<TValue>> _rows; 
    size_t _size;                   
    size_t _shift;                   
    size_t _count;                  

    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            hash += static_cast<size_t>(key[i]);
        }
        return hash % _size;
    }

    size_t hh(size_t hash) const noexcept {
        return (hash + _shift) % _size;
    }

    bool is_full() const noexcept {
        return _count >= _size;
    }
    void calculate_shift() {
        size_t start = _size / 15;
        if (start < 2) start = 2;

        for (size_t i = start; i < _size; ++i) {
            if (is_prime(i)) {
                _shift = i;
                return;
            }
        }
        _shift = 1;
    }

public:
    HashTableOA(size_t size = 10) : _size(size), _count(0) {
        if (_size < 2) _size = 2;
        calculate_shift();

        _rows = TVector<HashData<TValue>>(_size);

        for (size_t i = 0; i < _size; ++i) {
            _rows[i] = HashData<TValue>(); 
            _rows[i]._state = empty;      
        }
    }

    void insert(const std::string& key, const TValue& value) override {
        if (is_full()) {
            throw std::runtime_error("Hash table is full");
        }

        size_t hash = h(key);
        size_t first_hash = hash;
        int first_deleted = -1;

        while (true) {
            State& current_state = _rows[hash]._state;

            if (current_state == busy && _rows[hash]._key == key) {
                throw std::logic_error("Key already exists");
                //return;
            }

            if (current_state == empty) {
                size_t insert_pos = hash;
                if (first_deleted != -1) {
                    insert_pos = first_deleted;
                }

                _rows[insert_pos] = HashData<TValue>(key, value, busy);
                ++_count;
                return;
            }

            if (current_state == deleted && first_deleted == -1) {
                first_deleted = hash;
            }

            hash = hh(hash);
            if (hash == first_hash) {
                if (first_deleted != -1) {
                    _rows[first_deleted] = HashData<TValue>(key, value, busy);
                    ++_count;
                    return;
                }
                else {
                    throw std::logic_error("Hash table logic error: full cycle but no space");
                }
            }
        }
    }

    void erase(const std::string& key) override {
        size_t hash = h(key);
        size_t first_hash = hash;

        while (true) {
            State& current_state = _rows[hash]._state;

            if (current_state == empty) {
                break;
            }

            if (current_state == busy && _rows[hash]._key == key) {
                _rows[hash]._state = deleted;
                --_count;
                return;
            }

            hash = hh(hash);
            if (hash == first_hash) {
                break;
            }
        }

        throw std::runtime_error("Key not found");
    }

    const TValue& found(const std::string& key) const override {
        size_t hash = h(key);
        size_t first_hash = hash;

        while (true) {
            const State& current_state = _rows[hash]._state;

            if (current_state == empty) {
                break;
            }

            if (current_state == busy && _rows[hash]._key == key) {
                return _rows[hash]._value;
            }

            hash = hh(hash);
            if (hash == first_hash) {
                break; 
            }
        }

        throw std::runtime_error("Key not found");
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    void print(std::ostream& out) const override {
        for (size_t i = 0; i < _size; ++i) {
            if (_rows[i]._state == busy) {
                out << "[" << i << "] ";
                out << _rows[i]._key << " : " << _rows[i]._value;
            }
            out << std::endl;
        }
    }

    void read(std::istream& in) override {
        clear();
        std::string key;
        TValue value;
        while (in >> key >> value) {
            try {
                insert(key, value);
            }
            catch (const std::exception& e) {
            }
        }
    }

    void clear() {
        for (size_t i = 0; i < _size; ++i) {
            _rows[i] = HashData<TValue>();
        }
        _count = 0;
    }
};

