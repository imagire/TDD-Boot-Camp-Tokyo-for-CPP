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




const char* WayList[] = { "All", "ìdé‘" };
// èåèÅFsrc < dst 
const Place PlaceList[] = 
{
	{"â°ïl",PLACE_ID__YOKOHAMA},
	{"êÏçË",PLACE_ID__KAWASAKI},
	{"ïêë†è¨êô",PLACE_ID__MUSASHI_KOSUGI},
	{"êºçëï™éõ",PLACE_ID__NISHI_KOKUBUNJI},
	{"èaíJ",PLACE_ID__SHIBUYA},
	{"ìåãû",PLACE_ID__TOKYO},
	{"êVèh",PLACE_ID__SHINJUKU},
	{"å‰íÉÉmêÖ",PLACE_ID__OCHANOMIZU},
	{"èHótå¥",PLACE_ID__AKIHABARA},
	{"írë‹",PLACE_ID__IKEBUKURO},
	{"ìcí[",PLACE_ID__TABATA},
	{"ê‘âH",PLACE_ID__AKABANE},
	{"ìÏâYòa",PLACE_ID__MINAMI_URAWA},
	{"ëÂã{",PLACE_ID__OOMIYA},
//	{"ëÂìá",PLACE_ID__OOSHIMA}
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

// LinkÇµÇƒÇ¢ÇÍÇŒtrueÇï‘Ç∑
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
		// íºê⁄Ç¬Ç»Ç™Ç¡ÇƒÇ¢ÇÈÉPÅ[ÉX
		if( LinkList[ i ].srcid == src )
		{
			if( LinkList[ i ].dstid == dst )
			{
				return true;
			}
		}
	}

	// ä‘ê⁄ìIÇ…Ç¬Ç»Ç™Ç¡ÇƒÇÈÉPÅ[ÉXÅiçƒãAÅj
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
	// IDåüçı
	int iSrcId = SearchID( src );
	if( iSrcId == -1 ) return false;
	int iDstId = SearchID( dst );
	if( iDstId == -1 ) return false;

	// ìØÇ∂èÍçáÇÕtrueÇï‘Ç∑
	if( iSrcId == iDstId )
	{
		return true;
	}

	// ÉäÉìÉNÉäÉXÉgåüçı
	return IsLinked( iSrcId, iDstId );
}

TEST( TDDBC, Project1 )
{
	// ëÂã{Ç©ÇÁâ°ïlÇ÷ÇÕìdé‘Ç≈Ç¢ÇØÇÈ
	EXPECT_EQ( true, CanGo( "ëÂã{", "â°ïl", "ìdé‘" ));
	EXPECT_EQ( true, CanGo( "â°ïl", "ëÂã{", "ìdé‘" ));
	// ëÂìáÇ÷ÇÕâ°ïlÇ©ÇÁìdé‘Ç≈ÇÕÇ¢ÇØÇ»Ç¢
	EXPECT_EQ( false, CanGo( "ëÂìá", "â°ïl", "ìdé‘" ));
	EXPECT_EQ( false, CanGo( "â°ïl", "ëÂìá", "ìdé‘" ));
}

TEST( TDDBC, Project2 )
{
	// â°ïlÅÃìåãûÇ…Ç¢ÇØÇÈ(Ç«ÇÒÇ»éËíiÇ≈Ç‡)
	EXPECT_EQ( true, CanGo( "â°ïl", "ìåãû" ));
	EXPECT_EQ( true, CanGo( "ìåãû", "â°ïl" ));
	// ìåãûÅÃëÂã{Ç…Ç¢ÇØÇÈ(Ç«ÇÒÇ»éËíiÇ≈Ç‡)
	EXPECT_EQ( true, CanGo( "ìåãû", "ëÂã{" ));
	EXPECT_EQ( true, CanGo( "ëÂã{", "ìåãû" ));
}

TEST( TDDBC, Project3 )
{
	// â°ïlÅÃëÂã{Ç¢ÇØÇÈ(Ç«ÇÒÇ»éËíiÇ≈Ç‡)
	EXPECT_EQ( true, CanGo( "â°ïl", "ëÂã{" ));
	EXPECT_EQ( true, CanGo( "ëÂã{", "â°ïl" ));
}

TEST( TDDBC, Project4 )
{
	bool bResult = true;

	// ìØÇ∂âwÇÃèÍçáÇÕÇ¢ÇØÇÈ
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

	// ëSåoòHÇ¢ÇØÇÈ(ìdé‘ÅEëÂìáà»äO)
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