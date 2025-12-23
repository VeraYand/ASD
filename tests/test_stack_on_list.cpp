#include <gtest/gtest.h>
#include "../lib_stack_on_list/stack_on_list.h"

TEST(TestStackOnList, default_cons) {
	Stack<int> stack;
	EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackOnList, size_cons) {
	Stack<int> stack(4);
	
	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
}


TEST(TestStackOnList, copy_cons) {
	Stack<int> stack(4);
	stack.push(11);
	Stack<int> new_stack(stack);

	EXPECT_FALSE(new_stack.is_empty());
	EXPECT_FALSE(new_stack.is_full());
	EXPECT_EQ(11, new_stack.top());
}

TEST(TestStackOnList, push_to_empty_stack) {
	Stack<int> stack(4);
	stack.push(11);

	EXPECT_FALSE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
	EXPECT_EQ(11, stack.top());
}

TEST(TestStackOnList, push_to_full_stack) {
	Stack<int> stack(4);
	stack.push(11);
	stack.push(22);
	stack.push(33);
	stack.push(44);

	ASSERT_ANY_THROW(stack.push(55));
}

TEST(TestStackOnList, pop_to_no_empty_stack) {
	Stack<int> stack(4);
	stack.push(11);
	stack.push(22);
	stack.pop();
	EXPECT_FALSE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
	EXPECT_EQ(11, stack.top());
}

TEST(TestStackOnList, pop_to_empty_stack) {
	Stack<int> stack(4);

	ASSERT_ANY_THROW(stack.pop());
}

TEST(TestStackOnList, top_to_empty_stack) {
	Stack<int> stack(4);

	ASSERT_ANY_THROW(stack.top());
}

TEST(TestStackOnList, is_empty) {
	Stack<int> stack(4);
	stack.push(11);
	stack.push(22);
	Stack<int> new_stack(4);
	EXPECT_FALSE(stack.is_empty());
	EXPECT_TRUE(new_stack.is_empty());
}

TEST(TestStackOnList, is_full) {
	Stack<int> stack(4);
	stack.push(11);
	stack.push(22);
	stack.push(33);
	stack.push(44);
	Stack<int> new_stack(4);
	new_stack.push(1);
	EXPECT_TRUE(stack.is_full());
	EXPECT_FALSE(new_stack.is_full());
}

TEST(TestStackOnList, clear) {
	Stack<int> stack(4);
	stack.push(11);
	stack.push(22);
	stack.push(33);
	stack.push(44);
	stack.clear();

	EXPECT_TRUE(stack.is_empty());
	ASSERT_ANY_THROW(stack.pop());
}

