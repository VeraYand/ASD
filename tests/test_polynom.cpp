#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"


TEST(TestPolynom, default_constructor) {
    Polynom p;
    EXPECT_TRUE(p.is_zero());
    EXPECT_EQ(p.size(), 0);
    EXPECT_EQ(p.to_string(), "0");
}

TEST(TestPolynom, constructor_from_monom) {
    int powers1[] = { 2, 1, 0 };
    Monom m1(3.5, powers1);  
    Polynom p1(m1);
    EXPECT_FALSE(p1.is_zero());
    EXPECT_EQ(p1.size(), 1);
    EXPECT_EQ(p1.to_string(), "3.5x^2y");

    int powers2[] = { 0, 0, 0 };
    Monom m2(5.0, powers2);  
    Polynom p2(m2);
    EXPECT_EQ(p2.to_string(), "5");

    Monom m3(0.0, powers1); 
    Polynom p3(m3);
    EXPECT_TRUE(p3.is_zero());
}

TEST(TestPolynom, copy_constructor) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };
    Polynom p;
    p.add_monom(Monom(3.5, powers1));
    p.add_monom(Monom(-2.0, powers2));

    Polynom p_copy(p);
    EXPECT_EQ(p_copy.size(), 2);
    EXPECT_EQ(p_copy.to_string(), "3.5x^2y - 2xz^3");
    EXPECT_EQ(p.to_string(), p_copy.to_string());
}

TEST(TestPolynom, assignment_operator) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };
    Polynom p;
    p.add_monom(Monom(3.5, powers1));
    p.add_monom(Monom(-2.0, powers2));

    Polynom p_assign;
    p_assign = p;

    EXPECT_EQ(p_assign.size(), 2);
    EXPECT_EQ(p_assign.to_string(), "3.5x^2y - 2xz^3");
    EXPECT_EQ(p.to_string(), p_assign.to_string());
}

TEST(TestPolynom, plus_monom) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p;
    p += Monom(3.5, powers1);
    EXPECT_EQ(p.to_string(), "3.5x^2y");

    p += Monom(-2.0, powers2);
    EXPECT_EQ(p.to_string(), "3.5x^2y - 2xz^3");

    p += Monom(1.5, powers1);
    EXPECT_EQ(p.to_string(), "5x^2y - 2xz^3");
}

TEST(TestPolynom, sub_monom) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p;
    p += Monom(5.0, powers1);
    p -= Monom(1.5, powers1);
    EXPECT_EQ(p.to_string(), "3.5x^2y");

    p -= Monom(-2.0, powers2);
    EXPECT_EQ(p.to_string(), "3.5x^2y + 2xz^3");
}

TEST(TestPolynom, mult_monom) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };
    int powers3[] = { 1, 1, 0 };

    Polynom p;
    p.add_monom(Monom(3.5, powers1));  // 3.5x^2y
    p.add_monom(Monom(-2.0, powers2)); // -2xz^3

    Monom m(2.0, powers3); 
    p *= m;

    EXPECT_EQ(p.to_string(), "7x^3y^2 - 4x^2yz^3");
}

TEST(TestPolynom, div_monom) {
    int powers1[] = { 3, 2, 1 };
    int powers2[] = { 2, 1, 3 };
    int powers3[] = { 1, 1, 1 };

    Polynom p;
    p.add_monom(Monom(6.0, powers1));  
    p.add_monom(Monom(-4.0, powers2)); 

    Monom m(2.0, powers3); 
    p /= m;

    EXPECT_EQ(p.to_string(), "3x^2y - 2xz^2");

    Monom zero_monom(0.0, powers3);
    EXPECT_THROW(p /= zero_monom, std::logic_error);
}

TEST(TestPolynom, add) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p1;
    p1.add_monom(Monom(3.5, powers1));  
    p1.add_monom(Monom(-2.0, powers2)); 

    Polynom p2;
    p2.add_monom(Monom(1.5, powers1));  
    p2.add_monom(Monom(3.0, powers2));  

    Polynom result = p1 + p2;
    EXPECT_EQ(result.to_string(), "5x^2y + xz^3");
}

TEST(TestPolynom, sub) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p1;
    p1.add_monom(Monom(5.0, powers1));  
    p1.add_monom(Monom(4.0, powers2)); 

    Polynom p2;
    p2.add_monom(Monom(3.0, powers1));  
    p2.add_monom(Monom(2.0, powers2));  

    Polynom result = p1 - p2;
    EXPECT_EQ(result.to_string(), "2x^2y + 2xz^3");
}

TEST(TestPolynom, mult) {
    int powers1[] = { 2, 0, 0 };  
    int powers2[] = { 0, 1, 0 }; 
    int powers3[] = { 2, 1, 0 }; 

    Polynom p1;
    p1.add_monom(Monom(2.0, powers1));  // 2x^2
    p1.add_monom(Monom(3.0, powers2));  // 3y

    Polynom p2;
    p2.add_monom(Monom(4.0, powers1));  // 4x^2
    p2.add_monom(Monom(1.0, powers2));  // y

    Polynom result = p1 * p2;
    // (2x^2 + 3y) * (4x^2 + y) = 8x^4 + 2x^2y + 12x^2y + 3y^2 = 8x^4 + 14x^2y + 3y^2
    EXPECT_EQ(result.to_string(), "8x^4 + 14x^2y + 3y^2");
}


TEST(TestPolynom, add_monom) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 2, 1, 0 }; 

    Polynom p;
    p.add_monom(Monom(3.5, powers1));
    EXPECT_EQ(p.to_string(), "3.5x^2y");

    p.add_monom(Monom(1.5, powers2));
    EXPECT_EQ(p.to_string(), "5x^2y");

    p.add_monom(Monom(0.0, powers1));
    EXPECT_EQ(p.to_string(), "5x^2y");
}

TEST(TestPolynom, sort) {
    int powers1[] = { 2, 1, 0 }; 
    int powers2[] = { 3, 0, 0 };  
    int powers3[] = { 1, 0, 3 };  
    int powers4[] = { 0, 0, 2 };  

    Polynom p;
    p.add_monom(Monom(1.0, powers1));
    p.add_monom(Monom(2.0, powers2));
    p.add_monom(Monom(3.0, powers3));
    p.add_monom(Monom(4.0, powers4));

    p.sort(); 
    EXPECT_TRUE(p.is_sorted());
}

TEST(TestPolynom, remove_zero_monoms) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p;
    p.add_monom(Monom(3.5, powers1));
    p.add_monom(Monom(0.0, powers2));  
    p.add_monom(Monom(-3.5, powers1));  

    p.remove_zero_monoms();
    EXPECT_TRUE(p.is_zero());
}

TEST(TestPolynom, calculate) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };  
    int powers0[] = { 0, 0, 0 };

    Polynom p;
    p.add_monom(Monom(2.0, powers1));  // 2x^2y
    p.add_monom(Monom(3.0, powers2));  // 3xz^3
    p.add_monom(Monom(1.0, powers0));  // 1

    double values[] = { 2.0, 3.0, 4.0 };  
    // 2*(2^2)*3 + 3*2*(4^3) + 1 = 2*4*3 + 3*2*64 + 1 = 24 + 384 + 1 = 409
    EXPECT_DOUBLE_EQ(p.calculate(values), 409.0);
}

TEST(TestPolynom, input_output) {
    int powers1[] = { 2, 1, 0 };
    int powers2[] = { 1, 0, 3 };

    Polynom p;
    p.add_monom(Monom(3.5, powers1));
    p.add_monom(Monom(-2.0, powers2));

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3.5x^2y - 2xz^3");

    std::string input = "2x^2y+3xz^3";
    std::istringstream is(input);
    Polynom p_input;
    is >> p_input;
    EXPECT_EQ(p_input.to_string(), "2x^2y + 3xz^3");
}

TEST(TestPolynom, complex_operations) {
    int powers_x[] = { 1, 0, 0 };
    int powers_y[] = { 0, 1, 0 };

    Polynom p;
    p.add_monom(Monom(1.0, powers_x));
    p.add_monom(Monom(1.0, powers_y));

    Polynom square = p * p;
    EXPECT_EQ(square.to_string(), "x^2 + 2xy + y^2");

    double values[] = { 2.0, 3.0, 0.0 };
    EXPECT_DOUBLE_EQ(square.calculate(values), 25.0);
}

TEST(TestPolynom, zero_polynom) {
    Polynom p1;
    EXPECT_TRUE(p1.is_zero());

    int powers[] = { 1, 1, 1 };
    p1.add_monom(Monom(0.0, powers));
    EXPECT_TRUE(p1.is_zero());

    Polynom p2(Monom(0.0, powers));
    EXPECT_TRUE(p2.is_zero());

    Polynom p3(p1);
    EXPECT_TRUE(p3.is_zero());
}