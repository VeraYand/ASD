#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestList, default_cons) {
	List<int> list;
	EXPECT_TRUE(list.is_empty());
}


TEST(TestList, copy_cons) {
	List<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	List<int> new_list(list);

	EXPECT_FALSE(new_list.is_empty());
	EXPECT_EQ((list.head())->value, (new_list.head())->value);
	EXPECT_EQ((list.tail())->value, (new_list.tail())->value);
}

TEST(TestList, push_front) {
	List<int> list;
	list.push_front(11);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 11);
}

TEST(TestList, push_back) {
	List<int> list;
	list.push_back(11);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 11);
}

TEST(TestList, insert_pos) {
	List<int> list;
	list.push_front(11);
	list.push_back(22);
	list.insert(1, 33);
	list.insert(1, 44);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.head()->next)->value, 44);
	EXPECT_EQ((list.tail())->value, 33);
}

TEST(TestList, insert_node) {
	List<int> list;
	list.push_front(11);
	list.push_back(22);
	Node<int>* node(list.tail());
	list.insert(node, 33);
	Node<int>* node1(list.head()->next);
	list.insert(node1, 44);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 33);
	EXPECT_EQ((list.head()->next->next)->value, 44);
}


TEST(TestList, pop_front) {
	List<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	list.pop_front();

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 22);
	EXPECT_EQ((list.tail())->value, 33);
}

TEST(TestList, pop_back) {
	List<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	list.pop_back();

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 22);
}

TEST(TestList, erase_node) {
	List<int> list;
	list.push_front(11);
	list.push_back(22);
	Node<int>* node(list.head());
	list.erase(node);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 11);
}

TEST(TestList, erase_pos) {
	List<int> list;
	list.push_front(11);
	list.push_back(22);
	list.push_back(33);
	list.push_back(44);
	list.push_back(55);
	list.erase(4);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 44);
	ASSERT_NO_THROW(list.erase(2));
}


