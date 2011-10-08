#include <gtest/gtest.h>

int add(int x, int y)
{
    return x + y;
}

TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

enum TRAIN_STATION
{
	OMIYA = 0,
	YOKOHAMA,
	TOKYO,
	OSHIMA
};

bool cango(TRAIN_STATION start, TRAIN_STATION end)
{

	if(start == OMIYA)
	{
		if((end == YOKOHAMA) || (end == TOKYO))
		{
			return true;
		}
	}

	if(start == TOKYO)
	{
		if((end == OMIYA)||(end == YOKOHAMA))
		{
			return true;
		}
	}


	if(start == YOKOHAMA)
	{
		if((end == OMIYA)||(end == TOKYO))
		{
			return true;
		}
	}

	return false;
}

TEST(Train, Move)
{
	EXPECT_TRUE(cango(OMIYA,YOKOHAMA));
	EXPECT_FALSE(cango(OSHIMA,YOKOHAMA));
}

TEST(Train, Problem2)
{
	EXPECT_TRUE(cango(YOKOHAMA,TOKYO));
	EXPECT_TRUE(cango(TOKYO,YOKOHAMA));
	EXPECT_TRUE(cango(TOKYO,OMIYA));
	EXPECT_TRUE(cango(OMIYA,TOKYO));	
}

TEST(Train, Problem3)
{
	EXPECT_TRUE(cango(YOKOHAMA,OMIYA));
}
