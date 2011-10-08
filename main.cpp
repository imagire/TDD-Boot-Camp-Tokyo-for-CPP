#include <gtest/gtest.h>
#include "Train.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

TEST(Train, Problem1)
{
	EXPECT_TRUE (cango(YOKOHAMA,   OMIYA));
	EXPECT_TRUE (cango(OMIYA,      YOKOHAMA));
	EXPECT_FALSE(cango(YOKOHAMA,   OSHIMA));
	EXPECT_FALSE(cango(OSHIMA,     YOKOHAMA));
	EXPECT_FALSE(cango(OSHIMA,     OMIYA));
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

TEST(Train, Problem4)
{
    for(TRAIN_STATION i = OMIYA; i < MAX-1; i = static_cast<TRAIN_STATION>(i+1)) {
        for(TRAIN_STATION j = YOKOHAMA; j < MAX; j = static_cast<TRAIN_STATION>(j+1)) {
            if ( i== j ) continue;
            else if ((i == OSHIMA) || (j==OSHIMA)) {
                EXPECT_FALSE(cango(i, j));
            }else{
                EXPECT_TRUE(cango(i, j));
            }
	   }
    }
}