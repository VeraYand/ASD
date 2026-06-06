#include "experiment_bench.h"

#include "../lib_sorted_table_list/sorted_table_list.h"

#include <vector>

namespace {

    using bench::run_int_key_benchmark;
    using bench::TableValue;

    const std::vector<size_t> kSizes = bench::kBenchmarkSizes;

}  // namespace

void bench_unsorted_list(std::vector<bench::RowResult>& rows) {
    run_int_key_benchmark<SortedTableOnList<std::string, TableValue>>(
        "List (unsorted)", kSizes, rows,
        "O(n)", "O(n)", "O(n)");
}