//#include "experiment_bench.h"
//
//#include "../lib_sorted_table_arr/sorted_table_arr.h"
//
//#include <vector>
//
//namespace {
//
//using bench::run_int_key_benchmark;
//using bench::TableValue;
//
//const std::vector<size_t> kSizes = bench::kBenchmarkSizes;
//
//}  // namespace
//
//void bench_sorted_arr(std::vector<bench::RowResult>& rows) {
//    run_int_key_benchmark<SortedTableOnArr<std::string, TableValue>>(
//        "Vector (sorted)", kSizes, rows,
//        "O(n)", "O(log n)", "O(n)");
//}
