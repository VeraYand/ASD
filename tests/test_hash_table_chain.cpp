#include <gtest/gtest.h>
#include "../lib_hash_table_chain/hash_table_chain.h"


TEST(TestHashTableChain, default_cons) {
	HashTableChain<int> table;
	EXPECT_TRUE(table.is_empty());
}


TEST(TestHashTableChain, insert) {
	HashTableChain<int> table;
	table.insert("one", 11);
	table.insert("three", 33);
	table.insert("zero", 00);
	EXPECT_EQ(table.found("one"), 11);
}

TEST(TestHashTableChain, erase) {
	HashTableChain<int> table;
	table.insert("0", 11);
	table.insert("2", 33);
	table.insert("1", 22);

	EXPECT_NO_THROW(table.erase("1"));
	EXPECT_EQ(table.found("0"), 11);
}

TEST(TestHashTableChain, erase1) {
	HashTableChain<int> table;
	table.insert("0", 11);
	table.insert("2", 33);
	table.insert("1", 22);
	table.erase("1");

	EXPECT_ANY_THROW(table.found("1"));
}

TEST(TestHashTableChain, erase_non_existent) {
	HashTableChain<int> table;
	table.insert("0", 11);
	table.insert("2", 33);
	table.insert("1", 22);

	EXPECT_ANY_THROW(table.erase("9"));
}

TEST(TestHashTableChain, collision) {
	HashTableChain<int> table;
	table.insert("123", 11);
	table.insert("321", 33);
	table.insert("213", 00);
	table.insert("2", 22);
	EXPECT_EQ(table.found("123"), 11);
	EXPECT_EQ(table.found("321"), 33);
	EXPECT_EQ(table.found("213"), 00);
	EXPECT_EQ(table.found("2"), 22);
	table.erase("321");
	EXPECT_EQ(table.found("123"), 11);
	EXPECT_EQ(table.found("213"), 00);
	EXPECT_EQ(table.found("2"), 22);
	EXPECT_ANY_THROW(table.found("321"));
}
