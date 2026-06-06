#include <gtest/gtest.h>
#include "../lib_sorted_table_arr/sorted_table_arr.h"


TEST(TestSortedTableOnArr, default_cons) {
	SortedTableOnArr<int, int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestSortedTableOnArr, insert) {
	SortedTableOnArr<int, int> table;
	table.insert(1, 11);
	table.insert(3, 33);
	table.insert(0, 00);
	EXPECT_EQ(table.found(1), 11);
}

TEST(TestSortedTableOnArr, erase) {
	SortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_NO_THROW(table.erase(1));
}

TEST(TestSortedTableOnArr, erase1) {
	SortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);
	table.erase(1);

	EXPECT_ANY_THROW(table.found(1));
}

TEST(TestSortedTableOnArr, erase_non_existent) {
	SortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_ANY_THROW(table.erase(9));
}


