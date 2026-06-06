#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h"

TEST(TestBSTree, default_cons) {
	BSTree<int, std::string> tree;
	EXPECT_TRUE(tree.is_empty());
}

TEST(TestBSTree, insert) {
	BSTree<int, std::string> tree;
	tree.insert(0, "null");
	tree.insert(3, "three");
	tree.insert(1, "one");
	EXPECT_EQ(*(tree.found(0)), "null");
	EXPECT_EQ(*(tree.found(1)), "one");
	EXPECT_EQ(*(tree.found(3)), "three");
	//EXPECT_ANY_THROW(tree.found(2));
	EXPECT_FALSE(tree.is_empty());
}

TEST(TestBSTree, erase) {
	BSTree<int, std::string> tree;
	tree.insert(3, "three");
	tree.insert(1, "one");
	tree.insert(0, "null");
	tree.insert(2, "two");
	tree.insert(4, "four");
	tree.insert(5, "five");
	tree.insert(6, "six");
	tree.erase(4);

	EXPECT_EQ(*(tree.found(0)), "null");
	EXPECT_EQ(*(tree.found(1)), "one");
	EXPECT_EQ(*(tree.found(3)), "three");
	EXPECT_EQ(*(tree.found(5)), "five");
	//EXPECT_ANY_THROW(tree.found(4));
}

TEST(TestBSTree, erase_root) {
	BSTree<int, std::string> tree;
	tree.insert(3, "three");
	tree.insert(1, "one");
	tree.insert(0, "null");
	tree.insert(2, "two");
	tree.insert(4, "four");
	tree.insert(5, "five");
	tree.erase(3);

	EXPECT_EQ(*(tree.found(0)), "null");
	EXPECT_EQ(*(tree.found(1)), "one");
	EXPECT_EQ(*(tree.found(4)), "four");
	EXPECT_EQ(*(tree.found(5)), "five");
	//EXPECT_ANY_THROW(tree.found(3));
}

TEST(TestBSTree, erase_listochek) {
	BSTree<int, std::string> tree;
	tree.insert(3, "three");
	tree.insert(1, "one");
	tree.insert(0, "null");
	tree.insert(2, "two");
	tree.insert(4, "four");
	tree.insert(5, "five");
	tree.erase(0);
	tree.erase(5);

	EXPECT_EQ(*(tree.found(4)), "four");
	EXPECT_EQ(*(tree.found(1)), "one");
	EXPECT_EQ(*(tree.found(3)), "three");
	/*EXPECT_ANY_THROW(tree.found(0));
	EXPECT_ANY_THROW(tree.found(5));*/
}

TEST(TestBSTree, erase_min_right_with_children) {
	BSTree<int, std::string> tree;
	tree.insert(50, "three");
	tree.insert(30, "one");
	tree.insert(60, "null");
	tree.insert(10, "two");
	tree.insert(40, "four");
	tree.insert(70, "five");
	tree.insert(35, "six");
	tree.insert(37, "seven");
	tree.erase(30);

	EXPECT_EQ(*(tree.found(37)), "seven");
	EXPECT_EQ(*(tree.found(35)), "six");
	//EXPECT_ANY_THROW(tree.found(30));
}

