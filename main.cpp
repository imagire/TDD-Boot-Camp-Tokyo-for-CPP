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
  MINAMIURAWA
};

struct RootSet
{
  Station tar;
  Station dist;
  RootSet(Station _tar, Station _dist): tar(_tar), dist(_dist) {};
};


// 駅の路線図
Station stationRoot[] = {YOKOHAMA, TOKYO, OOMIYA, KAWASAKI, MUSASHIKOSUGI, SHIBUYA, SHINJYUKU, IKEBUKURO, AKABANE, 
TABATA, AKIHABARA, OTYANOMIZU, NISHIKOKUBUNJI, MINAMIURAWA};


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

class TrainTestP : public ::testing::TestWithParam<Station> {
  
};

/*
 * ParameterizedTestにチャレンジ！
 */
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
