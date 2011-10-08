#include <gtest/gtest.h>
#include "path.h"

class PathTest : public ::testing::Test {
protected:
	virtual void SetUp()
	{
		path.AddReach("‘å‹{", "“Œ‹ž");
		path.AddReach("“Œ‹ž", "‰¡•l");
	}

	Path path;
};

TEST_F(PathTest, IsArrivalTestFromOomiyaToYokohama)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("‘å‹{", "‰¡•l", result));

	expected_root.push_back("‘å‹{");
	expected_root.push_back("“Œ‹ž");
	expected_root.push_back("‰¡•l");

	EXPECT_EQ(expected_root, result);

}

TEST_F(PathTest, IsArrivalTestFromYokohamaToOomiya)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("‰¡•l", "‘å‹{", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹ž");
	expected_root.push_back("‘å‹{");

	EXPECT_EQ(expected_root, result);
}

TEST_F(PathTest, IsArrivalTestFromYokohamaToTokyo)
{
	Path::Root expected_root;
	Path::Root result;


	EXPECT_EQ(true, path.IsArrival("‰¡•l", "“Œ‹ž", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹ž");

	EXPECT_EQ(expected_root, result);
}

TEST_F(PathTest, IsArrivalTestFromYokohamaToOoshima)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(false, path.IsArrival("‰¡•l", "‘å“‡", result));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
