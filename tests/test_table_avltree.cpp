#include <gtest/gtest.h>
#include "../lib_table_avltree/table_avltree.h"


TEST(TestTableAVLTree, default_cons) {
	TableOnAVLTree<int, int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestTableAVLTree, insert) {
	TableOnAVLTree<int, int> table;
	table.insert(1, 11);
	table.insert(3, 33);
	table.insert(0, 00);
	EXPECT_EQ(table.found(1), 11);
}

TEST(TestTableAVLTree, erase) {
	TableOnAVLTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_NO_THROW(table.erase(1));
}

TEST(TestTableAVLTree, erase1) {
	TableOnAVLTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);
	table.erase(1);

	EXPECT_ANY_THROW(table.found(1));
}

TEST(TestTableAVLTree, erase_non_existent) {
	TableOnAVLTree<int, int> table;
	table.insert(0, 11);
	table.insert(2, 33);
	table.insert(1, 22);

	EXPECT_ANY_THROW(table.erase(9));
}


