#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

//TEST(TestTree, default_cons) {
//	Tree<int, std::string> tree;
//	EXPECT_TRUE(tree.is_empty());
//}
//
//TEST(TestTree, insert) {
//	Tree<int, std::string> tree;
//	tree.insert(0, "null");
//	tree.insert(3, "three");
//	tree.insert(1, "one");
//	EXPECT_EQ(tree.found(0), "null");
//	EXPECT_EQ(tree.found(1), "one");
//	EXPECT_EQ(tree.found(3), "three");
//	EXPECT_EQ(tree.found(2), nullptr);
//	EXPECT_FALSE(tree.is_empty());
//}
//
//TEST(TestTree, erase) {
//	Tree<int, std::string> tree;
//	tree.insert(3, "three");
//	tree.insert(1, "one");
//	tree.insert(0, "null");
//	tree.insert(2, "two");
//	tree.insert(4, "four");
//	tree.insert(5, "five");
//	tree.erase(4);
//
//	EXPECT_EQ(tree.found(0), "null");
//	EXPECT_EQ(tree.found(1), "one");
//	EXPECT_EQ(tree.found(3), "three");
//	EXPECT_EQ(tree.found(5), "five");
//	EXPECT_EQ(tree.found(4), nullptr);
//}
//
//
//
