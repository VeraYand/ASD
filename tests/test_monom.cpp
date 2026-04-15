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
    int powers1[] = { 3, 1, 2 };  
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

TEST(TestMonom, add) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(3.2, powers);

    Monom res = m1 + m2;
    const int* res_powers = res.getPowers();

    EXPECT_DOUBLE_EQ(res.getCoeff(), 8.7);
    EXPECT_EQ(res_powers[0], 2);
    EXPECT_EQ(res_powers[1], 1);
    EXPECT_EQ(res_powers[2], 3);
}

TEST(TestMonom, add1) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 2, 3 };
    Monom m1(5.5, powers1);
    Monom m2(3.2, powers2);

    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TestMonom, sub) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(3.2, powers);

    Monom res = m1 - m2;
    const int* res_powers = res.getPowers();

    EXPECT_DOUBLE_EQ(res.getCoeff(), 2.3);
    EXPECT_EQ(res_powers[0], 2);
    EXPECT_EQ(res_powers[1], 1);
    EXPECT_EQ(res_powers[2], 3);
}

TEST(TestMonom, sub1) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 2, 2, 3 };
    Monom m1(5.5, powers1);
    Monom m2(3.2, powers2);

    EXPECT_ANY_THROW(m1 - m2);
}

TEST(TestMonom, mult) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Monom res = m1 * m2;
    const int* res_powers = res.getPowers();

    EXPECT_DOUBLE_EQ(res.getCoeff(), 16.5);
    EXPECT_EQ(res_powers[0], 3);  
    EXPECT_EQ(res_powers[1], 3);  
    EXPECT_EQ(res_powers[2], 4);  
}

TEST(TestMonom, div) {
    int powers1[] = { 3, 3, 4 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(16.5, powers1);
    Monom m2(3.0, powers2);

    Monom res = m1 / m2;
    const int* res_powers = res.getPowers();

    EXPECT_DOUBLE_EQ(res.getCoeff(), 5.5);
    EXPECT_EQ(res_powers[0], 2);
    EXPECT_EQ(res_powers[1], 1);
    EXPECT_EQ(res_powers[2], 3);
}

TEST(TestMonom, div_by_zero) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(0.0, powers2);

    EXPECT_ANY_THROW(m1 / m2);
}

TEST(TestMonom, div_negative_power) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 3, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    EXPECT_ANY_THROW(m1 / m2);
}

TEST(TestMonom, mult_val) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m *= 2.0;
    const int* m_powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 11.0);
    EXPECT_EQ(m_powers[0], 2);
    EXPECT_EQ(m_powers[1], 1);
    EXPECT_EQ(m_powers[2], 3);
}

TEST(TestMonom, div_value) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    m /= 2.0;
    const int* m_powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.75);
    EXPECT_EQ(m_powers[0], 2);
    EXPECT_EQ(m_powers[1], 1);
    EXPECT_EQ(m_powers[2], 3);
}

TEST(TestMonom, div_by_zero_val) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    EXPECT_ANY_THROW(m /= 0.0);
}

TEST(TestMonom, parse) {
    Monom m = Monom::parse("5.5x^2y^1z^3");
    const int* powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 5.5);
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 3);
}

TEST(TestMonom, parse_without_coeff) {
    Monom m = Monom::parse("x^2y^3");
    const int* powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 1.0);
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 3);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_negative_coeff) {
    Monom m = Monom::parse("-3.5x^2y^1");
    const int* powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), -3.5);
    EXPECT_EQ(powers[0], 2);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_without_power) {
    Monom m = Monom::parse("2.5xy");
    const int* powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 2.5);
    EXPECT_EQ(powers[0], 1);
    EXPECT_EQ(powers[1], 1);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_constant) {
    Monom m = Monom::parse("7.5");
    const int* powers = m.getPowers();

    EXPECT_DOUBLE_EQ(m.getCoeff(), 7.5);
    EXPECT_EQ(powers[0], 0);
    EXPECT_EQ(powers[1], 0);
    EXPECT_EQ(powers[2], 0);
}

TEST(TestMonom, parse_negative_power) {
    EXPECT_ANY_THROW(Monom::parse("x^-2"));
}

TEST(TestMonom, parse_duplicate_var) {
    EXPECT_ANY_THROW(Monom::parse("x^2x^3"));
}

TEST(TestMonom, parse_invalid_char) {
    EXPECT_ANY_THROW(Monom::parse("x^2a^3"));
}

TEST(TestMonom, parse_empty) {
    EXPECT_ANY_THROW(Monom::parse(""));
}

TEST(TestMonom, to_string) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    std::string str = m.to_string();
    EXPECT_EQ(str, "5.5x^2yz^3");
}

TEST(TestMonom, to_string_zero) {
    Monom m(0.0, nullptr);

    std::string str = m.to_string();
    EXPECT_EQ(str, "0");
}

TEST(TestMonom, calculate) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);
    double values[] = { 1.5, 2, 3 };
    double res = m.calculate(values);

    EXPECT_EQ(res, 668.25);
}

