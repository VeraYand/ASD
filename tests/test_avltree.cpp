#include <gtest/gtest.h>
#include "../lib_avltree/avltree.h"

TEST(TestAVLree, default_cons) {
	AVLTree<int, std::string> tree;
	EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, insert_RR) {
	AVLTree<int, std::string> tree; //30      35
	tree.insert(30, "null");       //  \     /  \    /
	tree.insert(35, "one");       //   35   30  40
	tree.insert(40, "two");      //     \
			                    //      40   
	EXPECT_EQ(tree.get_root_data().first, 35);
}

TEST(TestAVLTree, insert_LL) {
	AVLTree<int, std::string> tree; // 30      20
	tree.insert(30, "null");       //  /      /  \    /
	tree.insert(20, "one");       //  20     10  30
	tree.insert(10, "two");      //  /
	                            //  10     
	EXPECT_EQ(tree.get_root_data().first, 20);
}

TEST(TestAVLTree, insert_LR) {
	AVLTree<int, std::string> tree; //30      30      20
	tree.insert(30, "null");       // /       /      /  \    /
	tree.insert(10, "one");       // 10      20     10  30
	tree.insert(20, "two");      //   \      /
	                            //    20    10     
	EXPECT_EQ(tree.get_root_data().first, 20);
}

TEST(TestAVLTree, insert_RL) {
	AVLTree<int, std::string> tree; //30     30      35
	tree.insert(30, "null");       //  \      \     /  \    /
	tree.insert(40, "one");       //   40     35   30  40
	tree.insert(35, "two");      //    /       \
		                        //    35       40   
	EXPECT_EQ(tree.get_root_data().first, 35);
}

TEST(TestAVLTree, insert) {
	AVLTree<int, std::string> tree;
	tree.insert(15, "null");
	tree.insert(10, "one");
	tree.insert(20, "two");
	tree.insert(9, "three");
	tree.insert(12, "four");
	tree.insert(8, "five");
	tree.insert(7, "six");
	EXPECT_EQ(*(tree.found(15)), "null");
	EXPECT_EQ(*(tree.found(10)), "one");
	EXPECT_EQ(*(tree.found(9)), "three");
	EXPECT_EQ(*(tree.found(7)), "six");
	EXPECT_EQ(tree.get_root_data().first, 10);
}

TEST(TestAVLTree, erase) {
	AVLTree<int, std::string> tree;
	tree.insert(15, "null");
	tree.insert(10, "one");
	tree.insert(20, "two");
	tree.insert(9, "three");
	tree.insert(12, "four");
	tree.insert(8, "five");
	tree.insert(7, "six");
	tree.erase(15);
	tree.erase(12);
	tree.erase(20);
	//EXPECT_ANY_THROW(tree.found(15));
	EXPECT_EQ(*(tree.found(10)), "one");
	EXPECT_EQ(*(tree.found(9)), "three");
	EXPECT_EQ(*(tree.found(7)), "six");
	EXPECT_EQ(tree.get_root_data().first, 8);
}

TEST(TestAVLTree, erase_root) {
	AVLTree<int, std::string> tree;
	tree.insert(15, "null");
	tree.insert(10, "one");
	tree.insert(20, "two");
	tree.insert(9, "three");
	tree.insert(12, "four");
	tree.insert(8, "five");
	tree.insert(7, "six");
	tree.erase(10);
	//EXPECT_ANY_THROW(tree.found(10));
	EXPECT_EQ(*(tree.found(9)), "three");
	EXPECT_EQ(*(tree.found(7)), "six");
	EXPECT_EQ(tree.get_root_data().first, 12);
}


TEST(TestAVLTree, double_rotate) {
	AVLTree<int, std::string> tree;

	tree.insert(40, "40");
	tree.insert(20, "40");
	tree.insert(60, "40");
	tree.insert(15, "40");
	tree.insert(25, "40");
	tree.insert(50, "40");
	tree.insert(70, "40");
	tree.insert(5, "40");
	tree.insert(45, "40");
	tree.insert(55, "40");
	tree.insert(65, "40");
	tree.insert(80, "40");
	tree.insert(75, "40");

	tree.erase(25);
	EXPECT_EQ(tree.get_root_data().first, 60);
}
