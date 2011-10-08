#include <gtest/gtest.h>
#include "path.h"

TEST(PathTest, IsArrivalTestFromOomiyaToYokohama)
{
	Path path;
	Path::Root expected_root;
	Path::Root result;

	path.AddReach("‘å‹{", "“Œ‹ž");
	path.AddReach("“Œ‹ž", "‰¡•l");

	EXPECT_EQ(true, path.IsArrival("‘å‹{", "‰¡•l", result));

	expected_root.push_back("‘å‹{");
	expected_root.push_back("“Œ‹ž");
	expected_root.push_back("‰¡•l");

	EXPECT_EQ(expected_root, result);

}

TEST(PathTest, IsArrivalTestFromYokohamaToOomiya)
{
	Path path;
	Path::Root expected_root;
	Path::Root result;

	path.AddReach("‘å‹{", "“Œ‹ž");
	path.AddReach("“Œ‹ž", "‰¡•l");

	EXPECT_EQ(true, path.IsArrival("‰¡•l", "‘å‹{", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹ž");
	expected_root.push_back("‘å‹{");

	EXPECT_EQ(expected_root, result);
}

TEST(PathTest, IsArrivalTestFromYokohamaToTokyo)
{
	Path path;
	Path::Root expected_root;
	Path::Root result;

	path.AddReach("‘å‹{", "“Œ‹ž");
	path.AddReach("“Œ‹ž", "‰¡•l");

	EXPECT_EQ(true, path.IsArrival("‰¡•l", "“Œ‹ž", result));

	expected_root.push_back("‰¡•l");
	expected_root.push_back("“Œ‹ž");

	EXPECT_EQ(expected_root, result);
}

#if 0
enum BASYO {
	OOMIYA = 0,
	YOKOHAMA,
	OOSIMA,
	TOKYO
};
BASYO ikeru[][2] = {
	{OOMIYA,YOKOHAMA},
	{YOKOHAMA, OOMIYA},
	{TOKYO, YOKOHAMA},
	{YOKOHAMA, TOKYO},
	{TOKYO, OOMIYA},
	{OOMIYA, TOKYO}
};

bool IsToutyaku(enum BASYO start, enum BASYO end)
{
	bool ret=false;
	for(int i = 0; i < sizeof(ikeru)/sizeof(ikeru[0]) ; ++i){
		if (start == ikeru[i][0] && end == ikeru[i][1]) {
			ret = true;
			break;
		}
	}
	return ret;
}

TEST(Work1, Test1)
{
	EXPECT_EQ(true, IsToutyaku(OOMIYA, YOKOHAMA));
	EXPECT_EQ(true, IsToutyaku(YOKOHAMA, OOMIYA));
	EXPECT_EQ(false, IsToutyaku(OOSIMA, YOKOHAMA));
	EXPECT_EQ(false, IsToutyaku(YOKOHAMA, OOSIMA));
}

TEST(Work2, Test1)
{
	EXPECT_EQ(true, IsToutyaku(YOKOHAMA, TOKYO));
	EXPECT_EQ(true, IsToutyaku(TOKYO, YOKOHAMA));
	EXPECT_EQ(true, IsToutyaku(OOMIYA, TOKYO));
	EXPECT_EQ(true, IsToutyaku(TOKYO, OOMIYA));
}
#endif
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
