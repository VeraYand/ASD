#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"


TEST(TestDSU, default_cons) {
	ASSERT_NO_THROW(DSU dsu());
}

TEST(TestDSU, size_cons) {
	ASSERT_NO_THROW(DSU dsu(6));
}

TEST(TestDSU, dsu_union) {
	DSU dsu(6);
	dsu.dsu_union(2, 5);
	EXPECT_EQ(dsu.find(5), 2);
}


