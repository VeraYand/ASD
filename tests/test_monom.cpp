#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

TEST(TestMonom, default_cons) {
    Monom m;
    EXPECT_EQ(m.getCoeff(), 0.0);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 0);
    EXPECT_EQ(powers[1], 0);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, param_cons) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    EXPECT_DOUBLE_EQ(m.getCoeff(), 5.5);
    const int* m_powers = m.getPowers();
    EXPECT_EQ(m_powers[0], 2);
    EXPECT_EQ(m_powers[1], 1);
    EXPECT_EQ(m_powers[2], 3);
}

TEST(TestMonom, copy_cons) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(m1);

    EXPECT_DOUBLE_EQ(m2.getCoeff(), 5.5);
    const int* m2_powers = m2.getPowers();
    EXPECT_EQ(m2_powers[0], 2);
    EXPECT_EQ(m2_powers[1], 1);
    EXPECT_EQ(m2_powers[2], 3);
}

TEST(TestMonom, compare_equal) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 1, 3 };
    Monom m1(5.5, powers1);
    Monom m2(3.2, powers2);  

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);
}

TEST(TestMonom, compare_not_equal) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 2, 3 };
    Monom m1(5.5, powers1);
    Monom m2(5.5, powers2);

    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 != m2);
}

TEST(TestMonom, compare_greater) {
    int powers1[] = { 3, 1, 2 };  // Больше по первой степени
    int powers2[] = { 2, 2, 3 };
    Monom m1(1.0, powers1);
    Monom m2(1.0, powers2);

    EXPECT_TRUE(m1 > m2);
    EXPECT_FALSE(m2 > m1);
}

TEST(TestMonom, compare_less) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 3, 1, 2 };
    Monom m1(1.0, powers1);
    Monom m2(1.0, powers2);

    EXPECT_TRUE(m1 < m2);
    EXPECT_FALSE(m2 < m1);
}

// Тесты арифметических операций
TEST(TestMonom, addition) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(3.2, powers);

    Monom sum = m1 + m2;

    EXPECT_DOUBLE_EQ(sum.getCoeff(), 8.7);
    const int* sum_powers = sum.getPowers();
    EXPECT_EQ(sum_powers[0], 2);
    EXPECT_EQ(sum_powers[1], 1);
    EXPECT_EQ(sum_powers[2], 3);
}

TEST(TestMonom, addition_throws) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 2, 3 };
    Monom m1(5.5, powers1);
    Monom m2(3.2, powers2);

    EXPECT_THROW(m1 + m2, std::logic_error);
}

TEST(TestMonom, subtraction) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(3.2, powers);

    Monom diff = m1 - m2;

    EXPECT_DOUBLE_EQ(diff.getCoeff(), 2.3);
    const int* diff_powers = diff.getPowers();
    EXPECT_EQ(diff_powers[0], 2);
    EXPECT_EQ(diff_powers[1], 1);
    EXPECT_EQ(diff_powers[2], 3);
}

TEST(TestMonom, subtraction_throws) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 2, 3 };
    Monom m1(5.5, powers1);
    Monom m2(3.2, powers2);

    EXPECT_THROW(m1 - m2, std::logic_error);
}

TEST(TestMonom, multiplication) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Monom prod = m1 * m2;

    EXPECT_DOUBLE_EQ(prod.getCoeff(), 16.5);
    const int* prod_powers = prod.getPowers();
    EXPECT_EQ(prod_powers[0], 3);  
    EXPECT_EQ(prod_powers[1], 3);  
    EXPECT_EQ(prod_powers[2], 4);  
}

TEST(TestMonom, division) {
    int powers1[] = { 3, 3, 4 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(16.5, powers1);
    Monom m2(3.0, powers2);

    Monom quot = m1 / m2;

    EXPECT_DOUBLE_EQ(quot.getCoeff(), 5.5);
    const int* quot_powers = quot.getPowers();
    EXPECT_EQ(quot_powers[0], 2);  
    EXPECT_EQ(quot_powers[1], 1);  
    EXPECT_EQ(quot_powers[2], 3);  
}

TEST(TestMonom, division_by_zero) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(0.0, powers2);

    EXPECT_THROW(m1 / m2, std::logic_error);
}

TEST(TestMonom, division_negative_power) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 3, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    EXPECT_THROW(m1 / m2, std::logic_error);
}

TEST(TestMonom, multiply_assign) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m *= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoeff(), 11.0);
    const int* m_powers = m.getPowers();
    EXPECT_EQ(m_powers[0], 2);
    EXPECT_EQ(m_powers[1], 1);
    EXPECT_EQ(m_powers[2], 3);
}

TEST(TestMonom, divide_assign) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m /= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.75);
    const int* m_powers = m.getPowers();
    EXPECT_EQ(m_powers[0], 2);
    EXPECT_EQ(m_powers[1], 1);
    EXPECT_EQ(m_powers[2], 3);
}

TEST(TestMonom, divide_assign_by_zero) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    EXPECT_THROW(m /= 0.0, std::logic_error);
}

TEST(TestMonom, add_assign) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m += 2.5;

    EXPECT_DOUBLE_EQ(m.getCoeff(), 8.0);
}

TEST(TestMonom, subtract_assign) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m -= 1.5;

    EXPECT_DOUBLE_EQ(m.getCoeff(), 4.0);
}

TEST(TestMonom, parse_simple) {
    Monom m = Monom::parse("5.5x^2y^1z^3");

    EXPECT_DOUBLE_EQ(m.getCoeff(), 5.5);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 3);
}

TEST(TestMonom, parse_without_coeff) {
    Monom m = Monom::parse("x^2y^3");

    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 3);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_negative_coeff) {
    Monom m = Monom::parse("-3.5x^2y^1");

    EXPECT_DOUBLE_EQ(m.getCoeff(), -3.5);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_without_power) {
    Monom m = Monom::parse("2.5xy");

    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.5);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 1);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_constant) {
    Monom m = Monom::parse("7.5");

    EXPECT_DOUBLE_EQ(m.getCoeff(), 7.5);
    const int* powers = m.getPowers();
    EXPECT_EQ(powers[0], 0);
    EXPECT_EQ(powers[1], 0);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_negative_power) {
    EXPECT_THROW(Monom::parse("x^-2"), std::logic_error);
}

TEST(TestMonom, parse_duplicate_var) {
    EXPECT_THROW(Monom::parse("x^2x^3"), std::logic_error);
}

TEST(TestMonom, parse_invalid_char) {
    EXPECT_THROW(Monom::parse("x^2a^3"), std::logic_error);
}

TEST(TestMonom, parse_empty) {
    EXPECT_THROW(Monom::parse(""), std::logic_error);
}

TEST(TestMonom, to_string_simple) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    std::string str = m.to_string();
    EXPECT_TRUE(str.find("5.5") != std::string::npos);
    EXPECT_TRUE(str.find("x^2") != std::string::npos || str.find("x2") != std::string::npos);
}

TEST(TestMonom, to_string_zero) {
    Monom m(0.0, nullptr);

    std::string str = m.to_string();
    EXPECT_EQ(str, "0");
}

