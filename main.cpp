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

enum PLACE_ID
{
	PLACE_ID_START,
	PLACE_ID__AKABANE,
	PLACE_ID__AKIHABARA,
	PLACE_ID__IKEBUKURO,
	PLACE_ID__KAWASAKI,
	PLACE_ID__MINAMI_URAWA,
	PLACE_ID__MUSASHI_KOSUGI,
	PLACE_ID__NISHI_KOKUBUNJI,
	PLACE_ID__OCHANOMIZU,
	PLACE_ID__OOMIYA,
	PLACE_ID__OOSHIMA,
	PLACE_ID__SHIBUYA,
	PLACE_ID__SHINJUKU,
	PLACE_ID__TABATA,
	PLACE_ID__TOKYO,
	PLACE_ID__YOKOHAMA,
	PLACE_ID_END
};
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
const Place PlaceList[] = 
{
	{"���l",PLACE_ID__YOKOHAMA},
	{"���",PLACE_ID__KAWASAKI},
	{"��������",PLACE_ID__MUSASHI_KOSUGI},
	{"��������",PLACE_ID__NISHI_KOKUBUNJI},
	{"�a�J",PLACE_ID__SHIBUYA},
	{"����",PLACE_ID__TOKYO},
	{"�V�h",PLACE_ID__SHINJUKU},
	{"�䒃�m��",PLACE_ID__OCHANOMIZU},
	{"�H�t��",PLACE_ID__AKIHABARA},
	{"�r��",PLACE_ID__IKEBUKURO},
	{"�c�[",PLACE_ID__TABATA},
	{"�ԉH",PLACE_ID__AKABANE},
	{"��Y�a",PLACE_ID__MINAMI_URAWA},
	{"��{",PLACE_ID__OOMIYA},
//	{"�哇",PLACE_ID__OOSHIMA}
};
const Link	LinkList[] = {
							{PLACE_ID__AKABANE, PLACE_ID__IKEBUKURO, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__AKABANE, PLACE_ID__MINAMI_URAWA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__AKABANE, PLACE_ID__TABATA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__AKIHABARA, PLACE_ID__TOKYO, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__AKIHABARA, PLACE_ID__OCHANOMIZU, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__AKIHABARA, PLACE_ID__TABATA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__IKEBUKURO, PLACE_ID__SHINJUKU, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__IKEBUKURO, PLACE_ID__TABATA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__KAWASAKI, PLACE_ID__MUSASHI_KOSUGI, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__KAWASAKI, PLACE_ID__TOKYO, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__KAWASAKI, PLACE_ID__YOKOHAMA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__MINAMI_URAWA, PLACE_ID__NISHI_KOKUBUNJI, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__MINAMI_URAWA, PLACE_ID__OOMIYA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__MUSASHI_KOSUGI, PLACE_ID__NISHI_KOKUBUNJI, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__MUSASHI_KOSUGI, PLACE_ID__SHIBUYA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__MUSASHI_KOSUGI, PLACE_ID__YOKOHAMA, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__NISHI_KOKUBUNJI, PLACE_ID__SHINJUKU, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__OCHANOMIZU, PLACE_ID__TOKYO, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__SHIBUYA, PLACE_ID__SHINJUKU, WAY_TRAIN, DIR_BOTH},
							{PLACE_ID__SHIBUYA, PLACE_ID__TOKYO, WAY_TRAIN, DIR_BOTH}
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

// Link���Ă����true��Ԃ�
#define SEARCH_LEVEL 10
int arLinkStack[SEARCH_LEVEL];
int iLinkStack = 0;
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
		for ( int j = iLinkStack; j == 0; --j)
		{
			if ( LinkList[i].srcid == LinkStack[j] )
			{

			}
		}

		if( LinkList[ i ].srcid == src )
		{
			int iNewSrc = LinkList[ i ].dstid;
			if( IsLinked( iNewSrc, dst ) )
			{
				return true;
			}
		}
		else if( LinkList[ i ].dstid == src )
		{
			int iNewSrc = LinkList[ i ].srcid;
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

	// �����ꍇ��true��Ԃ�
	if( iSrcId == iDstId )
	{
		return true;
	}

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

TEST( TDDBC, Project3 )
{
	// ���l�̑�{������(�ǂ�Ȏ�i�ł�)
	EXPECT_EQ( true, CanGo( "���l", "��{" ));
	EXPECT_EQ( true, CanGo( "��{", "���l" ));
}

TEST( TDDBC, Project4 )
{
	bool bResult = true;

	// �����w�̏ꍇ�͂�����
	for( int i = 0; i< sizeof( PlaceList ); i++ )
	{
		for( int j = 0; j< sizeof( PlaceList ); j++ )
		{
			if ( CanGo( PlaceList[i].name, PlaceList[j].name ) == false )
			{
				bResult = false;
			}
		}
	}

	// �S�o�H������(�d�ԁE�哇�ȊO)
	EXPECT_TRUE( bResult );
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