#include <gtest/gtest.h>

enum
{
	Station_Yokohama,
	Station_Ohshima,
	Station_Ohmiya
};

int add(int x, int y)
{
    return x + y;
}

bool is_reach(int start, int end)
{
	if( Station_Yokohama == start  && Station_Ohmiya == end)
	{
		return true;
	}

	return false;
}

TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}

TEST(AddTest, Exchange)
{
	EXPECT_FALSE(is_reach(Station_Yokohama,Station_Ohshima));
	EXPECT_TRUE(is_reach(Station_Yokohama,Station_Ohmiya));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

