#include <gtest/gtest.h>
#include "../lib_queue_on_list/queue_on_list.h"

TEST(TestQueueOnList, default_cons) {
	Queue<int> queue;
	EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueueOnList, size_cons) {
	Queue<int> queue(4);
	
	EXPECT_TRUE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
}


TEST(TestQueueOnList, copy_cons) {
	Queue<int> queue(4);
	queue.push(11);
	Queue<int> new_queue(queue);

	EXPECT_FALSE(new_queue.is_empty());
	EXPECT_FALSE(new_queue.is_full());
	EXPECT_EQ(queue.head(), new_queue.head());
	EXPECT_EQ(queue.tail(), new_queue.tail());
}

TEST(TestQueueOnList, push_to_empty_queue) {
	Queue<int> queue(4);
	queue.push(11);

	EXPECT_FALSE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
	EXPECT_EQ(queue.head(), 11);
	EXPECT_EQ(queue.tail(), 11);
}

TEST(TestQueueOnList, push_to_full_queue) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);

	ASSERT_ANY_THROW(queue.push(55));
}

TEST(TestQueueOnList, pop_to_no_empty_queue) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.pop();
	EXPECT_FALSE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
	EXPECT_EQ(22, queue.head());
	EXPECT_EQ(33, queue.tail());
}

TEST(TestQueueOnList, pop_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueueOnList, head_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.head());
}

TEST(TestQueueOnList, tail_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.tail());
}

TEST(TestQueueOnList, is_empty) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	Queue<int> new_queue(4);
	EXPECT_FALSE(queue.is_empty());
	EXPECT_TRUE(new_queue.is_empty());
}

TEST(TestQueueOnList, is_full) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);
	Queue<int> new_queue(4);
	new_queue.push(1);
	EXPECT_TRUE(queue.is_full());
	EXPECT_FALSE(new_queue.is_full());
}

TEST(TestQueueOnList, clear) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);
	queue.clear();

	EXPECT_TRUE(queue.is_empty());
	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueueOnList, pop_full_queue_and_push) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);
	queue.pop();
	queue.push(55);

	EXPECT_EQ(22, queue.head());
	EXPECT_EQ(55, queue.tail());
}

