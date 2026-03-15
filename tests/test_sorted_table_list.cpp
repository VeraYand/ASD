#include <gtest/gtest.h>
#include "../lib_sorted_table_list/sorted_table_list.h"


TEST(TestSortedTableOnList, default_cons) {
	SortedTableOnList<int, int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestSortedTableOnList, insert) {
	SortedTableOnList<int, int> table;
	table.insert(1, 11);
	table.insert(3, 33);
	table.insert(0, 00);
	EXPECT_EQ(table.find(1), 11);
}

//TEST(TestSortedTableOnList, erase) {
//	SortedTableOnList<int, int> table;
//	table.insert(0, 11);
//	table.insert(2, 33);
//	table.insert(1, 22);
//
//	EXPECT_NO_THROW(table.erase(1));
//}
//
//TEST(TestSortedTableOnList, erase1) {
//	SortedTableOnList<int, int> table;
//	table.insert(0, 11);
//	table.insert(2, 33);
//	table.insert(1, 22);
//	table.erase(1);
//
//	EXPECT_ANY_THROW(table.find(1));
//}

TEST(TestSortedTableOnList, erase_non_existent) {
	SortedTableOnList<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_ANY_THROW(table.erase(9));
}


