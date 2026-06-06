#pragma once

#include "../lib_hash_table_chain/hash_table_chain.h"
#include "../lib_hash_table_oa/hash_table_oa.h"

namespace bench {


template <class HashTable>
struct HashTableFactory;

template <class TValue>
struct HashTableFactory<HashTableChain<TValue>> {
    static HashTableChain<TValue> make(size_t capacity) {
        return HashTableChain<TValue>(capacity);
    }
};

template <class TValue>
struct HashTableFactory<HashTableOA<TValue>> {
    static HashTableOA<TValue> make(size_t capacity) {
        return HashTableOA<TValue>(capacity);
    }
};

}  // namespace bench
