#include <gtest/gtest.h>
#include "../lib_doubly_linked_list/doubly_linked_list.h"

TEST(TestDoublyLinkedList, default_cons) {
	DoublyLinkedList<int> list;
	EXPECT_TRUE(list.is_empty());
}


TEST(TestDoublyLinkedList, copy_cons) {
	DoublyLinkedList<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	DoublyLinkedList<int> new_list(list);

	EXPECT_FALSE(new_list.is_empty());
	EXPECT_EQ((list.head())->value, (new_list.head())->value);
	EXPECT_EQ((list.tail())->value, (new_list.tail())->value);
}

TEST(TestDoublyLinkedList, push_front) {
	DoublyLinkedList<int> list;
	list.push_front(11);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 11);
}

TEST(TestDoublyLinkedList, push_back) {
	DoublyLinkedList<int> list;
	list.push_back(11);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 11);
}

TEST(TestDoublyLinkedList, insert_pos) {
	DoublyLinkedList<int> list;
	list.push_front(11);
	list.push_back(22);
	list.insert(1, 33);
	list.insert(1, 44);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.head()->next)->value, 44);
	EXPECT_EQ((list.tail())->value, 33);
}

TEST(TestDoublyLinkedList, insert_node) {
	DoublyLinkedList<int> list;
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


TEST(TestDoublyLinkedList, pop_front) {
	DoublyLinkedList<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	list.pop_front();

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 22);
	EXPECT_EQ((list.tail())->value, 33);
}

TEST(TestDoublyLinkedList, pop_back) {
	DoublyLinkedList<int> list;
	list.push_back(11);
	list.push_back(22);
	list.push_back(33);
	list.pop_back();

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 22);
}

TEST(TestDoublyLinkedList, erase_node) {
	DoublyLinkedList<int> list;
	list.push_front(11);
	list.push_back(22);
	list.push_back(33);
	Node<int>* node(list.head());
	list.erase(node);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 33);
}

TEST(TestDoublyLinkedList, erase_pos) {
	DoublyLinkedList<int> list;
	list.push_front(11);
	list.push_back(22);
	list.push_back(33);
	list.push_back(44);
	list.push_back(55);
	list.erase(3);

	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ((list.head())->value, 11);
	EXPECT_EQ((list.tail())->value, 55);
	EXPECT_EQ((list.tail()->prev)->value, 33);
	ASSERT_NO_THROW(list.erase(2));
}


