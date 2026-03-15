#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"


TEST(TestPolynom, default_cons) {
    Polynom p;
    EXPECT_TRUE(p.is_zero());
    EXPECT_EQ(p.size(), 0);
}

TEST(TestPolynom, monom_cons) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);
    Polynom p(m);

    EXPECT_FALSE(p.is_zero());
    EXPECT_EQ(p.size(), 1);
}

TEST(TestPolynom, copy_cons) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Polynom p1;
    p1.insert_monom(m1);
    p1.insert_monom(m2);

    Polynom p2(p1);

    EXPECT_EQ(p2.size(), 2);
    EXPECT_FALSE(p2.is_zero());
}

TEST(TestPolynom, equality) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Polynom p1;
    p1.insert_monom(m1);
    p1.insert_monom(m2);

    Polynom p2;
    p2.insert_monom(m1);
    p2.insert_monom(m2);

    // Здесь нужно добавить оператор == для Polynom, если его нет
    //EXPECT_TRUE(p1 == p2);
}

TEST(TestPolynom, plus_assign) {
    int powers1[] = { 2, 2, 3 };
    int powers2[] = { 2, 2, 3 };

    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Polynom p1;
    p1.insert_monom(m1);

    Polynom p2;
    p2.insert_monom(m2);

    p1 += p2;

    EXPECT_EQ(p1.to_string(), "5.5x^2y^2z^3+3.0x^2y^2z^3");
}

TEST(TestPolynom, plus_assign_with_zero) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);

    Polynom p1;
    p1.insert_monom(m);

    Polynom p2;  

    p1 += p2;

    EXPECT_EQ(p1.size(), 1);
}

TEST(TestPolynom, plus_assign_cancellation) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(-5.5, powers);  

    Polynom p1;
    p1.insert_monom(m1);

    Polynom p2;
    p2.insert_monom(m2);

    p1 += p2; 

    EXPECT_TRUE(p1.is_zero());
    EXPECT_EQ(p1.size(), 0);
}


TEST(TestPolynom, plus) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };

    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Polynom p1;
    p1.insert_monom(m1);

    Polynom p2;
    p2.insert_monom(m2);

    Polynom p3 = p1 + p2;

    EXPECT_EQ(p3.size(), 2);
}

TEST(TestPolynom, minus_assign) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(2.5, powers);

    Polynom p1;
    p1.insert_monom(m1);

    Polynom p2;
    p2.insert_monom(m2);

    p1 -= p2;

    EXPECT_EQ(p1.size(), 1);
}

TEST(TestPolynom, minus_assign_cancellation) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(5.5, powers); 

    Polynom p1;
    p1.insert_monom(m1);

    Polynom p2;
    p2.insert_monom(m2);

    p1 -= p2; 

    EXPECT_TRUE(p1.is_zero());
}

TEST(TestPolynom, multiply_by_monom) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    int powers_mult[] = { 1, 0, 1 };

    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);
    Monom mult(2.0, powers_mult);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);

    Polynom result = p * mult;

    EXPECT_EQ(result.size(), 2);
}

TEST(TestPolynom, multiply_by_zero_monom) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom zero(0.0, nullptr);

    Polynom p;
    p.insert_monom(m1);

    Polynom result = p * zero;

    EXPECT_TRUE(result.is_zero());
}

TEST(TestPolynom, multiply_assign_by_monom) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };
    int powers_mult[] = { 1, 0, 1 };

    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);
    Monom mult(2.0, powers_mult);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);

    p *= mult;

    EXPECT_EQ(p.size(), 2);
}


TEST(TestPolynom, divide_by_monom) {
    int powers1[] = { 3, 2, 4 };
    int powers2[] = { 2, 3, 2 };
    int powers_div[] = { 1, 1, 1 };

    Monom m1(10.0, powers1);
    Monom m2(6.0, powers2);
    Monom div(2.0, powers_div);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);

    Polynom result = p / div;

    EXPECT_EQ(result.size(), 2);
}

TEST(TestPolynom, divide_by_zero_monom) {
    int powers[] = { 2, 1, 3 };
    Monom m(5.5, powers);
    Monom zero(0.0, nullptr);

    Polynom p;
    p.insert_monom(m);

    EXPECT_THROW(p / zero, std::logic_error);
}


TEST(TestPolynom, insert_monom) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };

    Monom m1(5.5, powers1);
    Monom m2(3.0, powers2);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);

    EXPECT_EQ(p.size(), 2);
}

TEST(TestPolynom, insert_similar_monom) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(2.5, powers); 

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2); 

    EXPECT_EQ(p.size(), 1);
}

TEST(TestPolynom, insert_zero_monom) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom zero(0.0, nullptr);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(zero);  

    EXPECT_EQ(p.size(), 1);
}

TEST(TestPolynom, insert_monom_cancellation) {
    int powers[] = { 2, 1, 3 };
    Monom m1(5.5, powers);
    Monom m2(-5.5, powers); 

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);  

    EXPECT_TRUE(p.is_zero());
}

TEST(TestPolynom, remove_zero_monoms) {
    int powers1[] = { 2, 1, 3 };
    int powers2[] = { 1, 2, 1 };

    Monom m1(5.5, powers1);
    Monom m2(0.0, powers2);  
    Monom m3(3.0, powers2);

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);
    p.insert_monom(m3);

    p.remove_zero_monoms();

    EXPECT_EQ(p.size(), 2);
}

TEST(TestPolynom, sort) {
    int powers1[] = { 1, 2, 1 };  
    int powers2[] = { 2, 1, 3 };  
    Monom m1(3.0, powers1);
    Monom m2(5.5, powers2);

    Polynom p;
    p.insert_monom(m1);  
    p.insert_monom(m2);  

    p.sort();

    EXPECT_TRUE(p.is_sorted());
}

//TEST(TestPolynom, is_sorted) {
//    int powers1[] = { 2, 1, 3 };
//    int powers2[] = { 1, 2, 1 };
//
//    Monom m1(5.5, powers1);
//    Monom m2(3.0, powers2);
//
//    Polynom p;
//    p.insert_monom(m1);
//    p.insert_monom(m2);
//
//    EXPECT_TRUE(p.is_sorted());
//}

TEST(TestPolynom, calculate) {
    int powers1[] = { 2, 1, 0 };  
    int powers2[] = { 1, 0, 1 };  

    Monom m1(2.0, powers1);  
    Monom m2(3.0, powers2);  

    Polynom p;
    p.insert_monom(m1);
    p.insert_monom(m2);

    double values[] = { 2.0, 3.0, 4.0 }; 

    double result = p.calculate(values);
    EXPECT_DOUBLE_EQ(result, 48.0);
}

TEST(TestPolynom, calculate_zero) {
    Polynom p;
    double values[] = { 2.0, 3.0, 4.0 };

    double result = p.calculate(values);
    EXPECT_DOUBLE_EQ(result, 0.0);
}


TEST(TestPolynom, empty_polynom_operations) {
    Polynom p1;
    Polynom p2;

    int powers[] = { 1, 1, 1 };
    Monom m(2.0, powers);

    p1 += p2;
    EXPECT_TRUE(p1.is_zero());

    p1 *= m;
    EXPECT_TRUE(p1.is_zero());

    p1 -= p2;
    EXPECT_TRUE(p1.is_zero());
}

//TEST(TestPolynom, large_polynom) {
//    Polynom p;
//
//    for (int i = 0; i < 10; i++) {
//        int powers[] = { i, i + 1, i + 2 };
//        Monom m(i * 1.5, powers);
//        p.insert_monom(m);
//    }
//
//    EXPECT_EQ(p.size(), 10);
//}

TEST(TestPolynom, zero_coeff_handling) {
    int powers[] = { 2, 1, 3 };
    Monom m1(0.0, powers);  
    Monom m2(5.5, powers);

    Polynom p;
    p.insert_monom(m1); 
    p.insert_monom(m2);

    EXPECT_EQ(p.size(), 1);
}

