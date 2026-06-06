#pragma once

#include "../lib_itable/itable.h"
#include "../lib_tvector/tvector.h"

#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>

template <class TValue>
struct ChainNode {
    std::string _key;
    TValue _value;
    ChainNode* _next;

    ChainNode() : _key(""), _value(), _next(nullptr) {}
    ChainNode(const std::string& key, const TValue& val, ChainNode* next = nullptr)
        : _key(key), _value(val), _next(next) {
    }
};

template <class TValue>
class HashTableChain : public ITable<std::string, TValue> {
private:
    TVector<ChainNode<TValue>*> _buckets;  
    size_t _size;                           
    size_t _count;                          

    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); ++i) {
            hash += static_cast<size_t>(key[i]);
        }
        return hash % _size;
    }

public:
    HashTableChain(size_t size = 10) : _size(size), _count(0) {
        if (_size < 2) _size = 2;

        _buckets = TVector<ChainNode<TValue>*>(_size);

        for (size_t i = 0; i < _size; ++i) {
            _buckets[i] = nullptr;
        }
    }

    ~HashTableChain() {
        clear();
    }

    void insert(const std::string& key, const TValue& value) override {
        size_t bucket = h(key);

        ChainNode<TValue>* current = _buckets[bucket];
        while (current != nullptr) {
            if (current->_key == key) {
                throw std::logic_error("Key already exists");
            }
            current = current->_next;
        }

        ChainNode<TValue>* new_node = new ChainNode<TValue>(key, value, _buckets[bucket]);
        _buckets[bucket] = new_node;
        ++_count;
    }

    void erase(const std::string& key) override {
        size_t bucket = h(key);

        ChainNode<TValue>* current = _buckets[bucket];
        ChainNode<TValue>* prev = nullptr;

        while (current != nullptr) {
            if (current->_key == key) {
                if (prev == nullptr) {
                    _buckets[bucket] = current->_next;
                }
                else {
                    prev->_next = current->_next;
                }

                delete current;
                --_count;
                return;
            }
            prev = current;
            current = current->_next;
        }

        throw std::runtime_error("Key not found");
    }

    const TValue& found(const std::string& key) const override {
        size_t bucket = h(key);

        ChainNode<TValue>* current = _buckets[bucket];
        while (current != nullptr) {
            if (current->_key == key) {
                return current->_value;
            }
            current = current->_next;
        }

        throw std::runtime_error("Key not found");
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    void print(std::ostream& out) const override {
        for (size_t i = 0; i < _size; ++i) {
            out << "Bucket " << i << ": ";
            ChainNode<TValue>* current = _buckets[i];

            if (current == nullptr) {
                out << "empty";
            }
            else {
                while (current != nullptr) {
                    out << "[" << current->_key << " : " << current->_value << "]";
                    if (current->_next != nullptr) {
                        out << " -> ";
                    }
                    current = current->_next;
                }
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
            ChainNode<TValue>* current = _buckets[i];
            while (current != nullptr) {
                ChainNode<TValue>* next = current->_next;
                delete current;
                current = next;
            }
            _buckets[i] = nullptr;
        }
        _count = 0;
    }

    

};