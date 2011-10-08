#include <gtest/gtest.h>
/*
int add(int x, int y)
{
    return x + y;
}

int sub(int x, int y)
{
	return x-y;
}
*/

struct Pair
{
	char* src;
	char* dst;
};

Pair arPair = 
{
	"‘å‹{", "‰¡•l"
};

bool CanGo( char* src, char* dst )
{
	if ( strcmp( arPair.src, src ) )
	{
		if ( strcmp( arPair.dst, dst ) )
		{
			return true;
		}
	}
	else if ( strcmp( arPair.src, dst ) )
	{
		if ( strcmp( arPair.dst, src ) )
		{
			return true;
		}
	}

	return false;
}

TEST( TDDBC, Project1 )
{
	EXPECT_EQ( true, CanGo( "‘å‹{", "‰¡•l" ));
	EXPECT_EQ( false, CanGo( "‘å“‡", "‰¡•l" ));
}
/*
TEST(AddTest, Test1)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(AddTest, Test2)
{
    EXPECT_EQ(3, add(1, 2));
}
TEST(SubTest, TestSub)
{
		EXPECT_EQ(1, sub(2,1));
}
*/
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
