#include <gtest/gtest.h>

int add(int x, int y)
{
    return x + y;
}

int sub(int x, int y)
{
    return x - y;
}

TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}

TEST(SubTest, Test3)
{
    EXPECT_EQ(1, sub(2, 1));
}

TEST(SubTest, Test4)
{
    EXPECT_EQ(-1, sub(2, 3));
}
	enum {OOMIYA=0, YOKOHAMA, OOSHIMA, TOKYO};
class Train {


public:
	Train () {};
	bool able(int from, int to) {
		bool result = false;
		//if (from == YOKOHAMA && to == OOSHIMA) result = false;

		if ((from == OOMIYA && to == YOKOHAMA) 
		||(from == YOKOHAMA && to == TOKYO)
		||(from == TOKYO && to == OOMIYA)) result = true;
		return result;
	}
};

TEST(TrainTest, Test1)
{
	Train train;

	EXPECT_TRUE(train.able(OOMIYA, YOKOHAMA));
	EXPECT_FALSE(train.able(YOKOHAMA, OOSHIMA));
}

TEST(TrainTest, Test2)
{
	Train train;

	EXPECT_TRUE(train.able(YOKOHAMA, TOKYO));
	EXPECT_TRUE(train.able(TOKYO, OOMIYA));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
