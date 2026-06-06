#include "experiment_bench.h"

#include "../lib_table_avltree/table_avltree.h"

#include <vector>

namespace {

using bench::run_int_key_benchmark;
using bench::TableValue;

const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  // namespace

void bench_sorted_avl(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<TableOnAVLTree<std::string, TableValue>>(
        "AVL (sorted)", kSizes, rows,
        "O(log n)", "O(log n)", "O(log n)");
}
