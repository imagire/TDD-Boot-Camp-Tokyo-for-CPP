#include <gtest/gtest.h>

typedef enum {
	OMIYA,
	YOKOHAMA,
	OSHIMA
} STATION;

extern bool checkTrainRoute(STATION station1, STATION station2);

TEST(checkTrainRouteTest, Test1)
{
    EXPECT_TRUE(checkTrainRoute(OMIYA,YOKOHAMA));
    EXPECT_TRUE(checkTrainRoute(YOKOHAMA,OMIYA));
}

TEST(checkTrainRouteTest, Test2)
{
	EXPECT_FALSE(checkTrainRoute(OSHIMA,YOKOHAMA));
	EXPECT_FALSE(checkTrainRoute(YOKOHAMA,OSHIMA));
    EXPECT_FALSE(checkTrainRoute(OMIYA,OMIYA));
    EXPECT_FALSE(checkTrainRoute(YOKOHAMA,YOKOHAMA));
    EXPECT_FALSE(checkTrainRoute(OSHIMA,OSHIMA));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

bool checkTrainRoute(STATION station1, STATION station2)
{
	if (station1 == OMIYA)
	{
		if (station2 == YOKOHAMA)
		{
			return true;
		}
	}
	else if (station2 == OMIYA)
	{
		if (station1 == YOKOHAMA)
		{
			return true;
		}
	}
	return false;
}
