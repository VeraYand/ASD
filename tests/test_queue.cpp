#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TestQueue, default_cons) {
	Queue<int> queue;
	EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueue, size_cons) {
	Queue<int> queue(4);
	
	EXPECT_TRUE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
}


TEST(TestQueue, copy_cons) {
	Queue<int> queue(4);
	queue.push(11);
	Queue<int> new_queue(queue);

	EXPECT_FALSE(new_queue.is_empty());
	EXPECT_FALSE(new_queue.is_full());
	EXPECT_EQ(queue.head(), new_queue.head());
	EXPECT_EQ(queue.tail(), new_queue.tail());
}

TEST(TestQueue, push_to_empty_queue) {
	Queue<int> queue(4);
	queue.push(11);

	EXPECT_FALSE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
	EXPECT_EQ(queue.head(), 11);
	EXPECT_EQ(queue.tail(), 11);
}

TEST(TestQueue, push_to_full_queue) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);

	ASSERT_ANY_THROW(queue.push(55));
}

TEST(TestQueue, pop_to_no_empty_queue) {
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

TEST(TestQueue, pop_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueue, head_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.head());
}

TEST(TestQueue, tail_to_empty_queue) {
	Queue<int> queue(4);

	ASSERT_ANY_THROW(queue.tail());
}

TEST(TestQueue, is_empty) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	Queue<int> new_queue(4);
	EXPECT_FALSE(queue.is_empty());
	EXPECT_TRUE(new_queue.is_empty());
}

TEST(TestQueue, is_full) {
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

TEST(TestQueue, clear) {
	Queue<int> queue(4);
	queue.push(11);
	queue.push(22);
	queue.push(33);
	queue.push(44);
	queue.clear();

	EXPECT_TRUE(queue.is_empty());
	ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueue, pop_full_queue_and_push) {
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

