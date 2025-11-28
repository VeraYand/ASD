#include <gtest/gtest.h>
#include "../lib_math_vector/math_vector.h"

#define EPSILON 0.000001

TEST(TestEasyExampleLib, can_make_base_math_vector) {

	ASSERT_NO_THROW(MathVector<int>());
}

TEST(TestEasyExampleLib, addition_math_vector_and_scalar) {
    int arr[] = { 1, 2, 3, 4 };
    MathVector<int> vec(4, arr);
    int arr_res[] = { 6, 7, 8, 9 };

    MathVector<int> actual_result = vec + 5;
    MathVector<int> expected_result(4, arr_res);

    EXPECT_EQ(expected_result, actual_result);
}

