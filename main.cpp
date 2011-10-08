#include <gtest/gtest.h>
#include "path.h"

class PathTest : public ::testing::Test {
protected:
	virtual void SetUp()
	{
		path.AddReach("‘å‹{", "“ì‰Y˜a");
		path.AddReach("“ì‰Y˜a", "Ô‰H");
		path.AddReach("“ì‰Y˜a", "¼‘•ª›");
		path.AddReach("Ô‰H", "’r‘Ü");
		path.AddReach("Ô‰H", "“c’[");
		path.AddReach("’r‘Ü", "Vh");
		path.AddReach("’r‘Ü", "“c’[");
		path.AddReach("“c’[", "H—tŒ´");
		path.AddReach("¼‘•ª›", "Vh");
		path.AddReach("¼‘•ª›", "•‘ ¬™");
		path.AddReach("Vh", "a’J");
		path.AddReach("Vh", "‚¨’ƒ‚Ì…");
		path.AddReach("‚¨’ƒ‚Ì…", "H—tŒ´");
		path.AddReach("‚¨’ƒ‚Ì…", "“Œ‹");
		path.AddReach("H—tŒ´", "“Œ‹");
		path.AddReach("a’J", "“Œ‹");
		path.AddReach("a’J", "•‘ ¬™");
		path.AddReach("“Œ‹", "ìè");
		path.AddReach("•‘ ¬™", "ìè");
		path.AddReach("•‘ ¬™", "‰¡•l");
		path.AddReach("ìè", "‰¡•l");
	}

	Path path;
};

TEST_F(PathTest, IsArrivalTestFromMinamiurawaToShibuya)
{
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("“ì‰Y˜a", "a’J", result));

	ASSERT_EQ(true, 2 <= result.size());
	EXPECT_EQ("“ì‰Y˜a", result[0]);
	EXPECT_EQ("a’J", result[result.size()-1]);

}

TEST_F(PathTest, IsArrivalTestChokutuu)
{
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("‘å‹{", "“ì‰Y˜a", result));
	EXPECT_EQ(true, path.IsArrival("“ì‰Y˜a", "¼‘•ª›", result));
	EXPECT_EQ(true, path.IsArrival("“ì‰Y˜a", "Ô‰H", result));
	EXPECT_EQ(true, path.IsArrival("Ô‰H", "’r‘Ü", result));
	EXPECT_EQ(true, path.IsArrival("’r‘Ü", "Vh", result));
	EXPECT_EQ(true, path.IsArrival("’r‘Ü", "“c’[", result));
}

TEST_F(PathTest, IsArrivalTestFromOomiyaToYokohama)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("‘å‹{", "‰¡•l", result));

	expected_root.push_back("‘å‹{");
	expected_root.push_back("“Œ‹");
	expected_root.push_back("‰¡•l");

	// EXPECT_EQ(expected_root, result);

}

TEST_F(PathTest, IsArrivalTestFromYokohamaToOomiya)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("‰¡•l", "‘å‹{", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹");
	expected_root.push_back("‘å‹{");

	// EXPECT_EQ(expected_root, result);
}

TEST_F(PathTest, IsArrivalTestFromYokohamaToTokyo)
{
	Path::Root expected_root;
	Path::Root result;


	EXPECT_EQ(true, path.IsArrival("‰¡•l", "“Œ‹", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹");

	// EXPECT_EQ(expected_root, result);
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
