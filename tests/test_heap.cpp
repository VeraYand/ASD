#include <gtest/gtest.h>
#include "../lib_heap/heap.h"

TEST(TestHeap, default_cons) {
	Heap<int> heap;
	EXPECT_TRUE(heap.is_empty());
}

TEST(TestHeap, insert) {
	Heap<int> heap;
	heap.insert(2);
	heap.insert(3);
	heap.insert(1);
	EXPECT_EQ(heap.get_root(), 1);
	EXPECT_FALSE(heap.is_empty());
}



