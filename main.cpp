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


// âwÇÃòHê¸ê}
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

class TrainTestP : public ::testing::TestWithParam<Station> {
  
};

/*
 * ParameterizedTestÇ…É`ÉÉÉåÉìÉWÅI
 */
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
