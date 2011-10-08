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


// 駅の路線図
Station stationRoot[] = {YOKOHAMA, TOKYO, OOMIYA, KAWASAKI, MUSASHIKOSUGI, SHIBUYA, SHINJYUKU, IKEBUKURO, AKABANE, 
TABATA, AKIHABARA, OTYANOMIZU, NISHIKOKUBUNJI, MINAMIURAWA};

// ルートの繋がりを表す列挙
RootSet stationRootSet[] = 
{
	RootSet(YOKOHAMA, KAWASAKI, 14),
	RootSet(YOKOHAMA, MUSASHIKOSUGI, 23),

	RootSet(MUSASHIKOSUGI, YOKOHAMA, 23),
	RootSet(KAWASAKI, TOKYO, 24),
	RootSet(MUSASHIKOSUGI, SHIBUYA, 21),
	RootSet(KAWASAKI, MUSASHIKOSUGI, 19),
};

// 一度通った駅
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
 * 2駅間にかかる時間を求める
 */
int getTakeTime(RootSet rootSet)
{
	passedSt.push_back(rootSet.tar);
	int size = sizeof(stationRootSet) / sizeof(stationRootSet[0]);
	for(int i = 0; i < size; ++i)
	{
		if(stationRootSet[i].tar == rootSet.tar){
			// 一致
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
 * 横浜->大宮は繋がっている
 */
TEST(TrainTest, YokohamaToOomiya)
{
  RootSet rootSet(YOKOHAMA, OOMIYA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 横浜->大島はつながっていない
 */
TEST(TrainTest, YokohamaNotToOoshima)
{
  RootSet rootSet(YOKOHAMA, OOSHIMA);
  EXPECT_FALSE(canGo(rootSet));
}

/*
 * 横浜->東京は繋がっている
 */
TEST(TrainTest, YokohamaToTokyo)
{
  RootSet rootSet(YOKOHAMA, TOKYO);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 東京 ->横浜は繋がっている
 */
TEST(TrainTest, TokyoToYokohama)
{
  RootSet rootSet(TOKYO, YOKOHAMA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 東京->大宮は繋がっている
 */
TEST(TrainTest, TokyoToOomiya)
{
  RootSet rootSet(TOKYO, OOMIYA);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 大宮->東京は繋がっている
 */
TEST(TrainTest, OomiyaToTokyo)
{
  RootSet rootSet(OOMIYA, TOKYO);
  EXPECT_TRUE(canGo(rootSet));
}



// AnywhereTest用のテストデータ
Station stationRootTest[] = {YOKOHAMA, TOKYO, OOMIYA, KAWASAKI, MUSASHIKOSUGI, SHIBUYA, SHINJYUKU, IKEBUKURO, AKABANE, 
TABATA, AKIHABARA, OTYANOMIZU, NISHIKOKUBUNJI, MINAMIURAWA};
/*
 * 色々な場所に行けることを確認しよう！
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
 * 横浜->川崎にかかる時間は14分
 */
TEST(TakeTime, YokohamaToKawasaki)
{
	RootSet rootSet(YOKOHAMA, KAWASAKI);
	EXPECT_EQ(14, getTakeTime(rootSet));
}

/*
 * 横浜->東京にかかる最短時間は38分
 */
TEST(TakeTime, YokohamaToTokyo)
{
	RootSet rootSet(YOKOHAMA, TOKYO);
	EXPECT_EQ(38, getTakeTime(rootSet));
}
/*
 * 横浜->渋谷にかかる最短時間は44分
 */
TEST(TakeTime, YokohamaToShibuya)
{
	RootSet rootSet(YOKOHAMA, SHIBUYA);
	EXPECT_EQ(54, getTakeTime(rootSet));
}

/*
 * ParameterizedTestにチャレンジ！
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
//INSTANTIATE_TEST_CASE_P(InstantionName, TrainTestP, ::testing::Values("横浜"));

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
