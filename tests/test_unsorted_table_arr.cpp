#include <gtest/gtest.h>
#include "../lib_unsorted_table_arr/unsorted_table_arr.h"


TEST(TestUnsortedTable, default_cons) {
	UnsortedTableOnArr<int, int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestUnsortedTable, insert) {
	UnsortedTableOnArr<int, int> table;
	table.insert(0, 11);
	EXPECT_EQ(table.find(0), 11);
}

TEST(TestUnsortedTable, erase) {
	UnsortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(1, 22);
	table.insert(2, 33);

	EXPECT_NO_THROW(table.erase(1));
}

TEST(TestUnsortedTable, erase1) {
	UnsortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(1, 22);
	table.insert(2, 33);
	table.erase(1);

	EXPECT_ANY_THROW(table.find(1));
}

TEST(TestUnsortedTable, erase_non_existent) {
	UnsortedTableOnArr<int, int> table;
	table.insert(0, 11);
	table.insert(1, 22);
	table.insert(2, 33);

	EXPECT_ANY_THROW(table.erase(9));
}


