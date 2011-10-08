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




const char* WayList[] = { "All", "電車" };
// 条件：src < dst 
const Place PlaceList[] = 
{
	{"横浜",PLACE_ID__YOKOHAMA},
	{"川崎",PLACE_ID__KAWASAKI},
	{"武蔵小杉",PLACE_ID__MUSASHI_KOSUGI},
	{"西国分寺",PLACE_ID__NISHI_KOKUBUNJI},
	{"渋谷",PLACE_ID__SHIBUYA},
	{"東京",PLACE_ID__TOKYO},
	{"新宿",PLACE_ID__SHINJUKU},
	{"御茶ノ水",PLACE_ID__OCHANOMIZU},
	{"秋葉原",PLACE_ID__AKIHABARA},
	{"池袋",PLACE_ID__IKEBUKURO},
	{"田端",PLACE_ID__TABATA},
	{"赤羽",PLACE_ID__AKABANE},
	{"南浦和",PLACE_ID__MINAMI_URAWA},
	{"大宮",PLACE_ID__OOMIYA},
//	{"大島",PLACE_ID__OOSHIMA}
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

// Linkしていればtrueを返す
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
		// 直接つながっているケース
		if( LinkList[ i ].srcid == src )
		{
			if( LinkList[ i ].dstid == dst )
			{
				return true;
			}
		}
	}

	// 間接的につながってるケース（再帰）
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
	// ID検索
	int iSrcId = SearchID( src );
	if( iSrcId == -1 ) return false;
	int iDstId = SearchID( dst );
	if( iDstId == -1 ) return false;

	// 同じ場合はtrueを返す
	if( iSrcId == iDstId )
	{
		return true;
	}

	// リンクリスト検索
	return IsLinked( iSrcId, iDstId );
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

TEST( TDDBC, Project2 )
{
	// 横浜⇔東京にいける(どんな手段でも)
	EXPECT_EQ( true, CanGo( "横浜", "東京" ));
	EXPECT_EQ( true, CanGo( "東京", "横浜" ));
	// 東京⇔大宮にいける(どんな手段でも)
	EXPECT_EQ( true, CanGo( "東京", "大宮" ));
	EXPECT_EQ( true, CanGo( "大宮", "東京" ));
}

TEST( TDDBC, Project3 )
{
	// 横浜⇔大宮いける(どんな手段でも)
	EXPECT_EQ( true, CanGo( "横浜", "大宮" ));
	EXPECT_EQ( true, CanGo( "大宮", "横浜" ));
}

TEST( TDDBC, Project4 )
{
	bool bResult = true;

	// 同じ駅の場合はいける
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

	// 全経路いける(電車・大島以外)
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