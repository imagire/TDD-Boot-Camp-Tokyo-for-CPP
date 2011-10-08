#include <gtest/gtest.h>
#include "Station.h"
int add(int x, int y)
{
    return x + y;
}

TEST(AddTest, Test1)
{
	EXPECT_TRUE( cango(eOhmiya, eYokohama ) );
	EXPECT_FALSE( cango(eYokohama, eOhshima ) );
}

TEST(CangoTest, YokohamaToOhmiya)
{
	EXPECT_TRUE( cango(eYokohama, eTokyo ) );
	EXPECT_TRUE( cango(eTokyo, eOhmiya ) );
}


TEST(AddTest, Test2)
{
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

bool cango(ESTATION_NAME rv_dep_station, ESTATION_NAME rv_dest_station){
	if(rv_dep_station == rv_dest_station){
		return false;//ÉGÉâÅ[.
	}
	else{
		if( (rv_dep_station == eOhmiya) && (rv_dest_station == eYokohama) ){
			return  true;
		}
		else if( (rv_dep_station == eYokohama) && (rv_dest_station == eOhshima) ){
			return false;
		}
		else if ( (rv_dep_station == eYokohama) && (rv_dest_station == eTokyo) ){
			return true;
		}
		else if ( ( rv_dep_station == eTokyo) && (rv_dest_station == eOhmiya) ){
			return true;
		}
		else{
			return false;
		}
	}
	return false;
}
