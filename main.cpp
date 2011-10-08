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

enum DIRECTION
{
	DIR_BOTH,
	DIR_FWD,
	DIR_REV
};

enum WAY
{
	WAY_ALL,
	WAY_TRAIN,
	WAY_MAX
};

struct Place
{
	char*	name;
	int		id;
};
struct Link
{
	int	srcid;
	int dstid;
	WAY way;
	DIRECTION direction;
};




const char* WayList[] = { "All", "�d��" };
// �����Fsrc < dst 
const Place PlaceList[] = {{"���l",1},{"����",2},{"��{",3},{"�哇",4}};
const Link	LinkList[] = {
							{1, 2, WAY_TRAIN, DIR_BOTH},
							{2, 3, WAY_TRAIN, DIR_BOTH} 
						 };

int SearchID( char* place )
{
	for( int i = 0; i< sizeof( PlaceList ); i++ )
	{
		if( strcmp(PlaceList[i].name, place ) == 0 )
		{
			return PlaceList[i].id;
		}
	}
	return -1;
}

// Link�C���f�b�N�X��Ԃ�
bool IsLinked( int src, int dst )
{
	if( src > dst )
	{
		int temp = src;
		src = dst;
		dst = temp;
	}

	for( int i = 0; i < sizeof( LinkList ); i++ )
	{
		// ���ڂȂ����Ă���P�[�X
		if( LinkList[ i ].srcid == src )
		{
			if( LinkList[ i ].dstid == dst )
			{
				return true;
			}
		}
	}

	// �ԐړI�ɂȂ����Ă�P�[�X�i�ċA�j
	for( int i = 0; i < sizeof( LinkList ); i++ )
	{
		// ���ڂȂ����Ă���P�[�X
		if( LinkList[ i ].srcid == src )
		{
			int iNewSrc = LinkList[ i ].dstid;
			if( IsLinked( iNewSrc, dst ) )
			{
				return true;
			}
		}
	}
	return false;
}

bool CanGo( char* src, char* dst, char* way = "All" )
{
	// ID����
	int iSrcId = SearchID( src );
	if( iSrcId == -1 ) return false;
	int iDstId = SearchID( dst );
	if( iDstId == -1 ) return false;

	// �����N���X�g����
	return IsLinked( iSrcId, iDstId );
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

TEST( TDDBC, Project2 )
{
	// ���l�̓����ɂ�����(�ǂ�Ȏ�i�ł�)
	EXPECT_EQ( true, CanGo( "���l", "����" ));
	EXPECT_EQ( true, CanGo( "����", "���l" ));
	// �����̑�{�ɂ�����(�ǂ�Ȏ�i�ł�)
	EXPECT_EQ( true, CanGo( "����", "��{" ));
	EXPECT_EQ( true, CanGo( "��{", "����" ));
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