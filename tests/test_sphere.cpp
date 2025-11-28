// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001

TEST(TestSphere, can_make_base_sphere) {

    ASSERT_NO_THROW(Sphere());
}

TEST(TestSphere, correctly_get_centre_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);


    Point3D actual_result = sphere.get_centre();

    Point3D expected_result = Point3D(99, 78, 54);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, correctly_get_rad_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);


    int actual_result = sphere.get_radius();

    int expected_result = 12;
    EXPECT_EQ(expected_result, actual_result);
}


TEST(TestSphere, check_base_constr_sphere) {
    Sphere sphere;

    bool actual_result = (sphere.get_centre() == Point3D(0, 0, 0)) && (sphere.get_radius() == 1);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, can_make_sphere) {

    ASSERT_NO_THROW(Sphere(Point3D(3, 9, 8), 7));
}

TEST(TestSphere, check_constr_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);

    bool actual_result = (sphere.get_centre() == Point3D(99, 78, 54)) && (sphere.get_radius() == 12);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, can_make_copy_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);
    ASSERT_NO_THROW(Sphere(sphere));
}

TEST(TestSphere, check_copy_constr_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);
    Sphere new_sphere(sphere);

    bool actual_result = (sphere.get_centre() == Point3D(99, 78, 54)) && (sphere.get_radius() == 12);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, check_equal_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);
    Sphere new_sphere(Point3D(99, 78, 54), 12);;

    bool actual_result = (sphere == new_sphere);

    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphere, check_equal1_sphere) {
    Sphere sphere(Point3D(99, 78, 54), 12);
    Sphere new_sphere(Point3D(809, 28, 54), 23);

    bool actual_result = (sphere == new_sphere);

    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}


TEST(TestSphere, throw_when_radius_not_positiv_sphere) {

    // Act & Assert
    ASSERT_ANY_THROW(Sphere(Point3D(99, 78, 54), -12));
}
