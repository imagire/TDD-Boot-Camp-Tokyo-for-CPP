#include <gtest/gtest.h>
#include <string>

enum Station
{
  YOKOHAMA,
  OOMIYA,
  OOSHIMA,
  TOKYO,
  KAWASAKI,
  MUSASHIKOSUGI, 
  SHIBUYA, SHINJYUKU, 
  IKEBUKURO, 
  AKABANE, 
  TABATA, 
  AKIHABARA, 
  OTYANOMIZU, 
  NISHIKOKUBUNJI, 
  MINAMIURAWA,
  STATION_NUM
};

struct RootSet
{
  Station tar;
  Station dist;
  int time;
  RootSet(Station _tar, Station _dist, int _time = 0): tar(_tar), dist(_dist), time(_time) {};
};


// âwÇÃòHê¸ê}
Station stationRoot[] = {YOKOHAMA, TOKYO, OOMIYA, KAWASAKI, MUSASHIKOSUGI, SHIBUYA, SHINJYUKU, IKEBUKURO, AKABANE, 
TABATA, AKIHABARA, OTYANOMIZU, NISHIKOKUBUNJI, MINAMIURAWA};

// ÉãÅ[ÉgÇÃåqÇ™ÇËÇï\Ç∑óÒãì
RootSet stationRootSet[] = 
{
	RootSet(YOKOHAMA, KAWASAKI, 14),
	RootSet(YOKOHAMA, MUSASHIKOSUGI, 23),

	RootSet(MUSASHIKOSUGI, YOKOHAMA, 23),
	RootSet(KAWASAKI, TOKYO, 24),
	RootSet(MUSASHIKOSUGI, SHIBUYA, 21),
	RootSet(KAWASAKI, MUSASHIKOSUGI, 19),
};

// àÍìxí Ç¡ÇΩâw
std::vector<Station> passedSt;

bool canGo(RootSet set)
{
  int size = sizeof(stationRoot) / sizeof(stationRoot[0]);

  for(int i = 0; i < size; ++i)
  {
    if(set.tar == stationRoot[i])
    {
      for(int j = 0; j < size; ++j)
      {
        if(set.dist == stationRoot[j])
          return true;
      }
    }
  }

  return false;
}


/*
 * 2âwä‘Ç…Ç©Ç©ÇÈéûä‘ÇãÅÇﬂÇÈ
 */
int getTakeTime(RootSet rootSet)
{
	passedSt.push_back(rootSet.tar);
	int size = sizeof(stationRootSet) / sizeof(stationRootSet[0]);
	for(int i = 0; i < size; ++i)
	{
		if(stationRootSet[i].tar == rootSet.tar){
			// àÍív
			if(stationRootSet[i].dist == rootSet.dist)
			{
				return stationRootSet[i].time;
			}
			RootSet subRootSet(stationRootSet[i].dist, rootSet.dist);
			bool isPassed = false;
			for(int j = 0; j < passedSt.size(); ++j)
			{
				if(passedSt[j] == stationRootSet[i].dist)
					isPassed = true;
			}
			if(!isPassed)
			{
				int retTime = getTakeTime(subRootSet);
				if(retTime != 0)
				{
					return stationRootSet[i].time + retTime;
				}
			}
		}
	}
	return 0;
}

/*
 * â°ïl->ëÂã{ÇÕåqÇ™Ç¡ÇƒÇ¢ÇÈ
 */
TEST(TrainTest, YokohamaToOomiya)
{
  RootSet rootSet(YOKOHAMA, OOMIYA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * â°ïl->ëÂìáÇÕÇ¬Ç»Ç™Ç¡ÇƒÇ¢Ç»Ç¢
 */
TEST(TrainTest, YokohamaNotToOoshima)
{
  RootSet rootSet(YOKOHAMA, OOSHIMA);
  EXPECT_FALSE(canGo(rootSet));
}

/*
 * â°ïl->ìåãûÇÕåqÇ™Ç¡ÇƒÇ¢ÇÈ
 */
TEST(TrainTest, YokohamaToTokyo)
{
  RootSet rootSet(YOKOHAMA, TOKYO);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ìåãû ->â°ïlÇÕåqÇ™Ç¡ÇƒÇ¢ÇÈ
 */
TEST(TrainTest, TokyoToYokohama)
{
  RootSet rootSet(TOKYO, YOKOHAMA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ìåãû->ëÂã{ÇÕåqÇ™Ç¡ÇƒÇ¢ÇÈ
 */
TEST(TrainTest, TokyoToOomiya)
{
  RootSet rootSet(TOKYO, OOMIYA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ëÂã{->ìåãûÇÕåqÇ™Ç¡ÇƒÇ¢ÇÈ
 */
TEST(TrainTest, OomiyaToTokyo)
{
  RootSet rootSet(OOMIYA, TOKYO);
  EXPECT_TRUE(canGo(rootSet));
}



// AnywhereTestópÇÃÉeÉXÉgÉfÅ[É^
Station stationRootTest[] = {YOKOHAMA, TOKYO, OOMIYA, KAWASAKI, MUSASHIKOSUGI, SHIBUYA, SHINJYUKU, IKEBUKURO, AKABANE, 
TABATA, AKIHABARA, OTYANOMIZU, NISHIKOKUBUNJI, MINAMIURAWA};
/*
 * êFÅXÇ»èÍèäÇ…çsÇØÇÈÇ±Ç∆ÇämîFÇµÇÊÇ§ÅI
 */
TEST(TrainTest, AnywhereTest)
{
  int size = sizeof(stationRootTest) / sizeof(stationRootTest[0]);
  for(int i = 0; i < size; ++i)
  {
    Station tar = stationRootTest[i];
    for(int j = 0; j < size; ++j)
    {
      Station dist = stationRootTest[j];
      RootSet rootSet(tar, dist);
      EXPECT_TRUE(canGo(rootSet));
    }
  }
}


/*
 * â°ïl->êÏçËÇ…Ç©Ç©ÇÈéûä‘ÇÕ14ï™
 */
TEST(TakeTime, YokohamaToKawasaki)
{
	RootSet rootSet(YOKOHAMA, KAWASAKI);
	EXPECT_EQ(14, getTakeTime(rootSet));
}

/*
 * â°ïl->ìåãûÇ…Ç©Ç©ÇÈç≈íZéûä‘ÇÕ38ï™
 */
TEST(TakeTime, YokohamaToTokyo)
{
	RootSet rootSet(YOKOHAMA, TOKYO);
	EXPECT_EQ(38, getTakeTime(rootSet));
}
/*
 * â°ïl->èaíJÇ…Ç©Ç©ÇÈç≈íZéûä‘ÇÕ44ï™
 */
TEST(TakeTime, YokohamaToShibuya)
{
	RootSet rootSet(YOKOHAMA, SHIBUYA);
	EXPECT_EQ(54, getTakeTime(rootSet));
}

/*
 * ParameterizedTestÇ…É`ÉÉÉåÉìÉWÅI
 */
class TrainTestP : public ::testing::TestWithParam<Station> {
  
};

TEST_P(TrainTestP, AllStationTest)
{
  Station station = GetParam();
  RootSet rootSet(station, station);
  EXPECT_TRUE(canGo(rootSet));
}

INSTANTIATE_TEST_CASE_P(InstantionName, TrainTestP, ::testing::Values(YOKOHAMA,TOKYO,OOMIYA));
//INSTANTIATE_TEST_CASE_P(InstantionName, TrainTestP, ::testing::Values("â°ïl"));

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
