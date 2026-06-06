#include <gtest/gtest.h>
#include "../lib_table_bstree/table_bstree.h"


//TEST(TestTableBSTree, default_cons) {
//	TableOnBSTree<int, int> table;
//	EXPECT_TRUE(table.is_empty());
//}
//
//
//TEST(TestTableBSTree, insert) {
//	TableOnBSTree<int, int> table;
//	table.insert(1, 11);
//	table.insert(3, 33);
//	table.insert(0, 00);
//	EXPECT_EQ(table.find(1), 11);
//}
//
//TEST(TestTableBSTree, erase) {
//	TableOnBSTree<int, int> table;
//	table.insert(0, 11);
//	table.insert(2, 33);
//	table.insert(1, 22);
//
//	EXPECT_NO_THROW(table.erase(1));
//}
//
//TEST(TestTableBSTree, erase1) {
//	TableOnBSTree<int, int> table;
//	table.insert(0, 11);
//	table.insert(2, 33);
//	table.insert(1, 22);
//	table.erase(1);
//
//	EXPECT_ANY_THROW(table.find(1));
//}
//
//TEST(TestTableBSTree, erase_non_existent) {
//	TableOnBSTree<int, int> table;
//	table.insert(0, 11);
//	table.insert(2, 33);
//	table.insert(1, 22);
//
//	EXPECT_ANY_THROW(table.erase(9));
//}
//
//
