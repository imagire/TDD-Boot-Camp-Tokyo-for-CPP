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
 * ���l->��{�͌q�����Ă���
 */
TEST(TrainTest, YokohamaToOomiya)
{
  RootSet rootSet(yokohama, oomiya);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ���l->�哇�͂Ȃ����Ă��Ȃ�
 */
TEST(TrainTest, YokohamaNotToOoshima)
{
  RootSet rootSet(yokohama, ooshima);
  EXPECT_FALSE(canGo(rootSet));
}

/*
 * ���l->�����͌q�����Ă���
 */
TEST(TrainTest, YokohamaToTokyo)
{
  RootSet rootSet(yokohama, tokyo);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ���� ->���l�͌q�����Ă���
 */
TEST(TrainTest, TokyoToYokohama)
{
  RootSet rootSet(tokyo, yokohama);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ����->��{�͌q�����Ă���
 */
TEST(TrainTest, TokyoToOomiya)
{
  RootSet rootSet(tokyo, oomiya);
  EXPECT_TRUE(canGo(rootSet));
}

/*
 * ��{->�����͌q�����Ă���
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
