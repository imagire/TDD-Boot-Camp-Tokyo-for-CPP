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




const char* WayList[] = { "All", "電車" };
// 条件：src < dst 
const Place PlaceList[] = {{"横浜",1},{"東京",2},{"大宮",3},{"大島",4}};
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

// Linkインデックスを返す
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
		// 直接つながっているケース
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
	// ID検索
	int iSrcId = SearchID( src );
	if( iSrcId == -1 ) return false;
	int iDstId = SearchID( dst );
	if( iDstId == -1 ) return false;

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