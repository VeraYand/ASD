#include <gtest/gtest.h>
#include <string>
#include "../lib_skip_list/skip_list.h"


TEST(SkipListTest, default_cons) {
    SkipList<int, std::string> sl(10);
    EXPECT_EQ(sl.find_nearest(10), nullptr);
}

TEST(SkipListTest, insert) {
    SkipList<int, std::string> sl;
    sl.insert(10, "ten");
    sl.insert(20, "twenty");
    sl.insert(5, "five");

    auto node = sl.find_nearest(20);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 20);
    EXPECT_EQ(node->data.second, "twenty");
}

TEST(SkipListTest, find_nearest) {
    SkipList<int, std::string> sl;
    sl.insert(10, "ten");
    sl.insert(20, "twenty");
    sl.insert(30, "thirty");

    auto node = sl.find_nearest(25);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 20);
}


TEST(SkipListTest, find_minimum) {
    SkipList<int, std::string> sl;
    sl.insert(10, "ten");
    sl.insert(20, "twenty");

    auto node = sl.find_nearest(5);
    EXPECT_EQ(node, nullptr);
}

TEST(SkipListTest, insertion_order) {
    SkipList<int, int> sl;
    sl.insert(3, 300);
    sl.insert(1, 100);
    sl.insert(2, 200);

    auto node = sl.get_head_at(0);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 1);

    node = node->next[0];
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 2);

    node = node->next[0];
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 3);
}

TEST(SkipListTest, large_insertions) {
    SkipList<int, int> sl(16);
    for (int i = 0; i < 100; ++i) {
        sl.insert(i, i * 10);
    }

    auto node = sl.find_nearest(50);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->data.first, 50);
    EXPECT_EQ(node->data.second, 500);
}






