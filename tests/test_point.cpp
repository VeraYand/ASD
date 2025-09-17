// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestEasyExampleLib, can_make_base_point) {

  ASSERT_NO_THROW(Point());
}

TEST(TestEasyExampleLib, correctly_get_x_point) {
    Point point(99, 78);


    int actual_result = point.get_x();

    int expected_result = 99;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, correctly_get_y_point) {
    Point point(99, 78);


    int actual_result = point.get_y();

    int expected_result = 78;
    EXPECT_EQ(expected_result, actual_result);
}


TEST(TestEasyExampleLib, check_base_constr_point) {
    Point point;

    bool actual_result = (point.get_x() == 0) && (point.get_y() == 0);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, can_make_point) {

    ASSERT_NO_THROW(Point(3, 9));
}

TEST(TestEasyExampleLib, check_constr_point) {
    Point point(99, 78);

    bool actual_result = (point.get_x() == 99) && (point.get_y() == 78);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, can_make_copy_point) {
    Point point(9, 8);
    ASSERT_NO_THROW(Point(point));
}

TEST(TestEasyExampleLib, check_copy_constr_point) {
    Point point(99, 78);
    Point new_point(point);

    bool actual_result = (point.get_x() == 99) && (point.get_y() == 78);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, check_equal_point) {
    Point point(99, 78);
    Point new_point(99, 78);

    bool actual_result = (point == new_point);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, check_equal1_point) {
    Point point(99, 78);
    Point new_point(49, 718);

    bool actual_result = (point == new_point);

    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}





