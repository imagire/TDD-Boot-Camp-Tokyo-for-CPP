#include <gtest/gtest.h>

int add(int x, int y)
{
    return x + y;
}

TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}
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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
