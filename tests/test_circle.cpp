// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001

TEST(TestCircle, can_make_base_circle) {

    ASSERT_NO_THROW(Circle());
}

TEST(TestCircle, correctly_get_centre_circle) {
    Circle circle(Point(99, 78), 12);


    Point actual_result = circle.get_centre();

    Point expected_result = Point(99, 78);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, correctly_get_rad_circle) {
    Circle circle(Point(99, 78), 12);


    int actual_result = circle.get_radius();

    int expected_result = 12;
    EXPECT_EQ(expected_result, actual_result);
}


TEST(TestCircle, check_base_constr_circle) {
    Circle circle;

    bool actual_result = (circle.get_centre() == Point(0, 0)) && (circle.get_radius() == 1);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, can_make_circle) {

    ASSERT_NO_THROW(Circle(Point(3, 9), 7));
}

TEST(TestCircle, check_constr_circle) {
    Circle circle(Point(99, 78), 12);

    bool actual_result = (circle.get_centre() == Point(99, 78)) && (circle.get_radius() == 12);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, can_make_copy_circle) {
    Circle circle(Point(99, 78), 12);
    ASSERT_NO_THROW(Circle(circle));
}

TEST(TestCircle, check_copy_constr_circle) {
    Circle circle(Point(99, 78), 12);
    Circle new_circle(circle);

    bool actual_result = (circle.get_centre() == Point(99, 78)) && (circle.get_radius() == 12);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, check_equal_circle) {
    Circle circle(Point(99, 78), 12);
    Circle new_circle(Point(99, 78), 12);

    bool actual_result = (circle == new_circle);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircle, check_equal1_circle) {
    Circle circle(Point(99, 78), 12);
    Circle new_circle(Point(54, 22), 92);

    bool actual_result = (circle == new_circle);

    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}


TEST(TestCircle, throw_when_radius_not_positive_circle) {

  // Act & Assert
  ASSERT_ANY_THROW(Circle(Point(99, 78), -12));
}
