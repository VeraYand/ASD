#include <gtest/gtest.h>
#include "../lib_priority_queue/priority_queue.h"

TEST(TestPriorityQueue, default_cons) {
	PriorityQueue<std::string> queue;
	EXPECT_TRUE(queue.is_empty());
}

TEST(TestPriorityQueue, insert) {
	PriorityQueue<std::string> queue;
	queue.insert("three", 2);
	queue.insert("one", 0);
	queue.insert("two", 0);
	auto node = queue.top();
	EXPECT_EQ(node.data, "one");
	EXPECT_FALSE(queue.is_empty());
}

TEST(TestPriorityQueue, erase) {
	PriorityQueue<std::string> queue;
	queue.insert("three", 2);
	queue.insert("one", 0);
	queue.insert("two", 0);
	queue.erase();
	queue.erase();
	auto node = queue.top();
	EXPECT_EQ(node.data, "three");
	EXPECT_FALSE(queue.is_empty());
}



