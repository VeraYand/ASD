#include <gtest/gtest.h>
#include"../lib_tvector/tvector.h"

TEST(TVectorTest, create_default_vector) {
    ASSERT_NO_THROW(TVector<int> vec());
}

TEST(TVectorTest, create_vector_with_given_size) {
    ASSERT_NO_THROW(TVector<int> vec(5));
}

TEST(TVectorTest, create_vector_from_array) {
    int arr[] = { 1, 2, 3 };

    ASSERT_NO_THROW(TVector<int> vec(3, arr));
}

TEST(TVectorTest, create_vector_from_other_vector) {
    TVector<int> vec1(6);

    ASSERT_NO_THROW(TVector<int> vec(vec1));
}

TEST(TVectorTest, default_vector_properties) {
    TVector<int> vec;

    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
}

TEST(TVectorTest, vector_with_given_size_properties) {
    TVector<int> vec(5);

    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(5, vec.capacity());
}

TEST(TVectorTest, vector_from_array_properties) {
    int arr[] = { 1, 2, 3 };

    TVector<int> vec(3, arr);

    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(18, vec.capacity()); 
}

TEST(TVectorTest, vector_from_other_vector_properties) {
    TVector<int> vec1(6);

    TVector<int> vec(vec1);

    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(6, vec.capacity());
}

TEST(TVectorTest, get_front_element) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(1, vec.front());
}

TEST(TVectorTest, get_back_element) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(3, vec.back());
}

TEST(TVectorTest, get_begin) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(1, *(vec.begin()));
}

TEST(TVectorTest, get_end) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(3, *(vec.end() - 1));
}

TEST(TVectorTest, check_empty) {
    TVector<int> vec;

    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, access_element_with_at) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(2, vec.at(1));
}

TEST(TVectorTest, access_invalid_index_with_at) {
    TVector<int> vec;

    ASSERT_THROW(vec.at(20), std::exception);
}

TEST(TVectorTest, access_element_with_operator) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    EXPECT_EQ(2, vec[1]);
}

TEST(TVectorTest, clear_vector) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    vec.clear();

    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(15, vec.capacity()); 
}

TEST(TVectorTest, emplace_element) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);

    vec.emplace(1, 22);

    EXPECT_EQ(22, vec.at(1));
}

TEST(TVectorTest, reserve_capacity) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);

    vec.reserve(25);

    EXPECT_EQ(25, vec.capacity());
}

TEST(TVectorTest, push_back_int) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);

    vec.push_back(55);

    EXPECT_EQ(55, vec.at(4));
}

TEST(TVectorTest, push_back_char) {
    char arr[] = { 'a', 'b', 'c', 'd' };
    TVector<char> vec(4, arr);

    vec.push_back('e');

    EXPECT_EQ('e', vec.at(4));
}

TEST(TVectorTest, insert_element) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);

    vec.insert(2, 33);

    EXPECT_EQ(33, vec.at(2));
}

TEST(TVectorTest, push_front_element) {
    int arr[] = { 1, 2, 3 };
    TVector<int> vec(3, arr);

    vec.push_front(11);

    EXPECT_EQ(11, vec[0]);
}

TEST(TVectorTest, pop_back) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    vec.pop_back();

    EXPECT_EQ(3, vec.size());
}

TEST(TVectorTest, erase) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    vec.erase(2);
    int expected_result = vec.size();

    EXPECT_EQ(3, vec.size());
}

TEST(TVectorTest, check_size_with_pop_front) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    vec.pop_front();

    EXPECT_EQ(3, vec.size());
}

TEST(TVectorTest, check_element_with_pop_front) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    vec.pop_front();

    EXPECT_EQ(2, vec.at(0));
}

TEST(TVectorTest, check_less_size_with_resize) {
    int arr[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(5, arr);
    vec.resize(3);

    EXPECT_EQ(3, vec.size());
}

TEST(TVectorTest, check_more_size_with_resize) {
    int arr[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec(5, arr);
    vec.resize(9);

    EXPECT_EQ(9, vec.size());
}

TEST(TVectorTest, check_default_element_with_resize) {
    char arr[] = { 'a', 'b', 'c', 'd', 'f' };
    TVector<char> vec(5, arr);
    vec.resize(9);

    EXPECT_EQ(0, vec[5]);
}

TEST(TVectorTest, check_element_with_resize) {
    char arr[] = { 'a', 'b', 'c', 'd', 'f' };
    TVector<char> vec(5, arr);
    vec.resize(9, 'k');

    EXPECT_EQ('k', vec[5]);
}

TEST(TVectorTest, get_front_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_back();
    vec.pop_front();

    EXPECT_EQ(2, vec.front());
}

TEST(TVectorTest, get_back_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_back();
    vec.pop_front();

    EXPECT_EQ(5, vec.back());
}

TEST(TVectorTest, at_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(1);
    vec.pop_back();
    vec.pop_front();

    EXPECT_EQ(4, vec.at(1));
}

TEST(TVectorTest, push_back_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_back();
    vec.pop_front();
    vec.push_back(55);

    EXPECT_EQ(55, vec.back());
}

TEST(TVectorTest, insert_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_front();
    vec.insert(2, 33);

    EXPECT_EQ(33, vec[2]);
}

TEST(TVectorTest, push_front_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_front();
    vec.push_front(11);

    EXPECT_EQ(11, vec[0]);
}

TEST(TVectorTest, size_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_front();
    vec.pop_back();

    EXPECT_EQ(3, vec.size());
}

TEST(TVectorTest, resize_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_back();
    vec.pop_front();
    vec.resize(9);

    EXPECT_EQ(9, vec.size());
}

TEST(TVectorTest, element_with_resize_with_deleted) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec(6, arr);
    vec.erase(3);
    vec.pop_back();
    vec.pop_front();
    vec.resize(9, 777);

    EXPECT_EQ(777, vec[5]);
}

TEST(TVectorTest, vectors_equal) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    int arr1[] = { 1, 2, 3, 4 };
    TVector<int> vec1(4, arr1);

    EXPECT_TRUE(vec == vec1);
}

TEST(TVectorTest, vectors_with_different_elements_not_equal) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    int arr1[] = { 1, 2, 3, 44 };
    TVector<int> vec1(4, arr1);

    EXPECT_FALSE(vec == vec1);
}

TEST(TVectorTest, vectors_with_different_sizes_not_equal) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    int arr1[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, arr1);

    EXPECT_FALSE(vec == vec1);
}

TEST(TVectorTest, vectors_with_different_sizes_not_equal_not_equal_operator) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    int arr1[] = { 1, 2, 3, 4, 5 };
    TVector<int> vec1(5, arr1);

    EXPECT_TRUE(vec != vec1);
}

TEST(TVectorTest, copy_assignment_from_same_type) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);

    TVector<int> vec1 = vec;

    EXPECT_TRUE(vec == vec1);
}

TEST(TVectorTest, copy_assignment_to_empty_vector) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    TVector<int> vec1;

    vec1 = vec;

    EXPECT_TRUE(vec == vec1);
}

TEST(TVectorTest, copy_assignment_to_non_empty_vector) {
    int arr[] = { 1, 2, 3, 4 };
    int arr1[] = { 11, 22, 33, 44 };
    TVector<int> vec(4, arr);
    TVector<int> vec1(4, arr1);

    vec1 = vec;

    EXPECT_TRUE(vec == vec1);
}

TEST(TVectorTest, reserve_preserves_content) {
    int arr[] = { 1, 2, 3, 4 };
    TVector<int> vec(4, arr);
    TVector<int> vec1(4, arr);

    vec.reserve(25);

    EXPECT_TRUE(vec == vec1);
}

TEST(TVectorTest, mixing) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec1(6, arr);
    TVector<int> vec2(6, arr);
    mixing(vec1);

    EXPECT_TRUE(vec1 != vec2);
}

TEST(TVectorTest, sorting) {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    TVector<int> vec1(6, arr);
    TVector<int> vec2(6, arr);
    mixing(vec1);
    sorting(vec1);

    EXPECT_TRUE(vec1 == vec2);
}




