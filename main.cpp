#include <gtest/gtest.h>
#include "Train.h"

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
