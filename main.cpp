#include <gtest/gtest.h>
#include "Train.h"

Station stYokohama(YOKOHAMA);
Station stTokyo(TOKYO);
Station stOmiya(OMIYA);

void createStation() {
    stYokohama.addStation(stTokyo);
    stTokyo.addStation(stYokohama);
    stOmiya.addStation(stTokyo);
    stTokyo.addStation(stOmiya);
} 

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

/*
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
*/

TEST(Train, Problem3)
{
    vector<Station> stopped;
	EXPECT_TRUE(stYokohama.canGo(stOmiya, stopped));
}

/*
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
*/

