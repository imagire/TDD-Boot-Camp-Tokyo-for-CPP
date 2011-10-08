#include <gtest/gtest.h>
#include "Station.h"
int add(int x, int y)
{
    return x + y;
}

TEST(AddTest, Test1)
{
	EXPECT_TRUE( cango(eYokohama, eOhmiya) );
}

TEST(AddTest, Test2)
{
    EXPECT_FALSE( cango(eYokohama, eOhshima) );
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

bool cango(ESTATION_NAME rv_dep_station, ESTATION_NAME rv_dest_station){
	if(rv_dep_station == rv_dest_station){
		//ÉGÉâÅ[.
	}
	else{
		if( (rv_dep_station == eOhmiya) && (rv_dep_station == eYokohama) ){
			return  true;
		}
		else{
			return false;
		}
	}
	return false;
}
