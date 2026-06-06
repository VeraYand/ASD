#include "experiment_bench.h"
#include "../lib_unsorted_table_arr/unsorted_table_arr.h"
#include <vector>

namespace {

    using bench::run_int_key_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  // namespace

void bench_unsorted_arr(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<UnsortedTableOnArr<std::string, TableValue>>(
        "Vector (unsorted)",
        kSizes,
        rows,
        "O(n)",
        "O(n)",
        "O(n)"
    );
}