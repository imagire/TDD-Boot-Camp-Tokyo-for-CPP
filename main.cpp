#include <gtest/gtest.h>
#include <string>

enum Station
{
  yokohama,
  oomiya,
  ooshima,
  tokyo
};

struct RootSet
{
  Station tar;
  Station dist;
  RootSet(Station _tar, Station _dist): tar(_tar), dist(_dist) {};
};

bool canGo(RootSet set)
{
  bool ret = false;

  if(yokohama == set.tar)
  {
    if(oomiya == set.dist
      || tokyo == set.dist)
      ret = true;
  }
  else if(tokyo == set.tar)
  {
    if(yokohama == set.dist || oomiya == set.dist)
    {
      return true;
    }
  }
  else if(oomiya == set.tar)
  {
    if(tokyo == set.dist)
    {
      return true;
    }
  }

  return ret;
}

/*
 * 横浜->大宮は繋がっている
 */
TEST(TrainTest, YokohamaToOomiya)
{
  RootSet rootSet(yokohama, oomiya);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 横浜->大島はつながっていない
 */
TEST(TrainTest, YokohamaNotToOoshima)
{
  RootSet rootSet(yokohama, ooshima);
  EXPECT_FALSE(canGo(rootSet));
}

/*
 * 横浜->東京は繋がっている
 */
TEST(TrainTest, YokohamaToTokyo)
{
  RootSet rootSet(yokohama, tokyo);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 東京 ->横浜は繋がっている
 */
TEST(TrainTest, TokyoToYokohama)
{
  RootSet rootSet(tokyo, yokohama);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 東京->大宮は繋がっている
 */
TEST(TrainTest, TokyoToOomiya)
{
  RootSet rootSet(tokyo, oomiya);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * 大宮->東京は繋がっている
 */
TEST(TrainTest, OomiyaToTokyo)
{
  RootSet rootSet(oomiya, tokyo);
  EXPECT_TRUE(canGo(rootSet));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
