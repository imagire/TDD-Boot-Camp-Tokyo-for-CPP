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




const char* WayList[] = { "All", "ìdé‘" };
// èåèÅFsrc < dst 
const Place PlaceList[] = {{"â°ïl",1},{"ìåãû",2},{"ëÂã{",3},{"ëÂìá",4}};
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

// LinkÉCÉìÉfÉbÉNÉXÇï‘Ç∑
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
		// íºê⁄Ç¬Ç»Ç™Ç¡ÇƒÇ¢ÇÈÉPÅ[ÉX
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
	// IDåüçı
	int iSrcId = SearchID( src );
	if( iSrcId == -1 ) return false;
	int iDstId = SearchID( dst );
	if( iDstId == -1 ) return false;

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