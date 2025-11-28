// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

#define EPSILON 0.000001

TEST(TestPoint3d, can_make_base_point3d) {

    ASSERT_NO_THROW(Point3D());
}

TEST(TestPoint3d, correctly_get_x_point3d) {
    Point3D point(99, 78, 22);


    int actual_result = point.get_x();

    int expected_result = 99;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, correctly_get_y_point3d) {
    Point3D point(99, 78, 22);


    int actual_result = point.get_y();

    int expected_result = 78;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, correctly_get_z_point3d) {
    Point3D point(99, 78, 22);


    int actual_result = point.get_z();

    int expected_result = 22;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, check_base_constr_point3d) {
    Point3D point;

    bool actual_result = (point.get_x() == 0) && (point.get_y() == 0) && (point.get_z() == 0);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, can_make_point3d) {

    ASSERT_NO_THROW(Point3D(3, 9, 1));
}

TEST(TestPoint3d, check_constr_point3d) {
    Point3D point(99, 78, 22);

    bool actual_result = ((point.get_x() == 99) && (point.get_y() == 78)) && (point.get_z() == 22);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, can_make_copy_point3d) {
    Point3D point(9, 8, 2);
    ASSERT_NO_THROW(Point3D(point));
}

TEST(TestPoint3d, check_copy_constr_point3d) {
    Point3D point(99, 78, 22);
    Point3D new_point(point);

    bool actual_result = ((point.get_x() == 99) && (point.get_y() == 78)) && (point.get_z() == 22);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, check_equal_point3d) {
    Point3D point(99, 78, 22);
    Point3D new_point(99, 78, 22);

    bool actual_result = (point == new_point);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestPoint3d, check_equal1_point3d) {
    Point3D point(99, 78, 22);
    Point3D new_point(49, 718, 99);

    bool actual_result = (point == new_point);

    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}




