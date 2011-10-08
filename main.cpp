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
	OOSIMA
};

bool IsToutyaku(enum BASYO start, enum BASYO end)
{
	bool ret=false;
	if (start == OOMIYA && end == YOKOHAMA) {
		ret = true;
	}
	else if (start == OOMIYA && end == YOKOHAMA) {
		ret = false;
	}
	else {
		ret = false;
	}
	return ret;
}

TEST(Work1, Test1)
{
	EXPECT_EQ(true, IsToutyaku(OOMIYA, YOKOHAMA));
	EXPECT_EQ(false, IsToutyaku(OOSIMA, YOKOHAMA));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
