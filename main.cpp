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
	"��{", "���l"
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
	// ��{���牡�l�ւ͓d�Ԃł�����
	EXPECT_EQ( true, CanGo( "��{", "���l", "�d��" ));
	EXPECT_EQ( true, CanGo( "���l", "��{", "�d��" ));
	// �哇�ւ͉��l����d�Ԃł͂����Ȃ�
	EXPECT_EQ( false, CanGo( "�哇", "���l", "�d��" ));
	EXPECT_EQ( false, CanGo( "���l", "�哇", "�d��" ));
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