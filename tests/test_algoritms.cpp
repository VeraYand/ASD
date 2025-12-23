#include <gtest/gtest.h>
#include "../lib_algoritms/algoritms.cpp"
//перенести в ветку algorithms в проект Algorithms


#ifdef BRECKETS
TEST(TestBracket, test_1) {
    EXPECT_TRUE(check_breckets("()"));
    EXPECT_TRUE(check_breckets("[]"));
    EXPECT_TRUE(check_breckets("{}"));
    EXPECT_FALSE(check_breckets("]"));
    EXPECT_FALSE(check_breckets("("));
    EXPECT_FALSE(check_breckets("(]"));
    EXPECT_FALSE(check_breckets("[])"));
    EXPECT_FALSE(check_breckets("()}}"));
    EXPECT_TRUE(check_breckets("() ()"));
    EXPECT_TRUE(check_breckets("{ () } []"));
    EXPECT_FALSE(check_breckets("{ () } [] ("));
    EXPECT_TRUE(check_breckets("({[([])]})"));
}

#endif


#ifdef ISLOOPED
TEST(TestListLibIterator, is_looped_true) {
    List<int> list;
    list.push_back(1);
    Node<int>* cur = list.head();
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.tail()->next = cur->next;

    EXPECT_EQ(true, is_looped(&list));


    list.tail()->next = nullptr;
};

TEST(TestListLibIterator, is_looped_false) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    EXPECT_FALSE(is_looped(&list));
};


#endif // ISLOOPED

#ifdef HAREANDTURTLE
TEST(TestHareAndTurtle, is_looped_true) {
    List<int> list;
    list.push_back(1);
    Node<int>* cur = list.head();
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.tail()->next = cur->next;

    EXPECT_EQ(true, is_looped_two(&list));


    list.tail()->next = nullptr;
};

TEST(TestHareAndTurtle, is_looped_false) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    EXPECT_FALSE(is_looped_two(&list));
};


#endif 

#ifdef ISLOOPEDPOS

TEST(TestISLOOPEDPOS, is_looped_true) {

    List<int> list;
    list.push_back(1);
    Node<int>* cur = list.head();
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.tail()->next = cur->next;

    EXPECT_EQ(2, is_looped_pos(&list));


    list.tail()->next = nullptr;
};

TEST(TestHareAndTurtle, is_looped_false) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    EXPECT_FALSE(is_looped_pos(&list));
};


#endif

