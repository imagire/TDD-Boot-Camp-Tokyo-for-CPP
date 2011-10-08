#include <gtest/gtest.h>
#pragma comment( lib, "./lib/gtest_maind.lib")
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
	"大宮", "横浜"
};

bool CanGo( char* src, char* dst, char* way )
{
	if ( strcmp( arPair.src, src ) == 0 )
	{
		if ( strcmp( arPair.dst, dst ) == 0 )
		{
			return true;
		}
	}
	else if ( strcmp( arPair.src, dst ) == 0 )
	{
		if ( strcmp( arPair.dst, src ) == 0 )
		{
			return true;
		}
	}

	return false;
}

TEST( TDDBC, Project1 )
{
	// 大宮から横浜へは電車でいける
	EXPECT_EQ( true, CanGo( "大宮", "横浜", "電車" ));
	EXPECT_EQ( true, CanGo( "横浜", "大宮", "電車" ));
	// 大島へは横浜から電車ではいけない
	EXPECT_EQ( false, CanGo( "大島", "横浜", "電車" ));
	EXPECT_EQ( false, CanGo( "横浜", "大島", "電車" ));
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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
*/