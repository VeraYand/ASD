#include <gtest/gtest.h>
#include "../lib_table_tree/table_tree.h"


TEST(TestTableTree, default_cons) {
	TableOnTree<int, int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestTableTree, insert) {
	TableOnTree<int, int> table;
	table.insert(1, 11);
	table.insert(3, 33);
	table.insert(0, 00);
	EXPECT_EQ(table.found(1), 11);
}

TEST(TestTableTree, erase) {
	TableOnTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);
	table.insert(3, 44);
	table.insert(4, 55);
	table.insert(5, 66);
	table.insert(6, 77);
	table.insert(7, 88);
	table.erase(2);

	EXPECT_EQ(table.found(3), 44);
	EXPECT_EQ(table.found(7), 88);
	EXPECT_ANY_THROW(table.found(2));
}

TEST(TestTableTree, erase1) {
	TableOnTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);
	table.erase(1);

	EXPECT_ANY_THROW(table.found(1));
}

TEST(TestTableTree, erase_non_existent) {
	TableOnTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_ANY_THROW(table.erase(9));
}


