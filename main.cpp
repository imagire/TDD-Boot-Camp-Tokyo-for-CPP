#include <gtest/gtest.h>
#include "Station.h"
int add(int x, int y)
{
    return x + y;
}

bool cango(ESTATION_NAME rv_dep_station, ESTATION_NAME rv_dest_station);

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

bool is_can_go[eSTATION_NAME_MAX][eSTATION_NAME_MAX] = {
	{false, true, false, true},
	{true, false, false, true},
	{false, false, false, false},
	{true, true, false, false}
};

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

bool cango(ESTATION_NAME rv_dep_station, ESTATION_NAME rv_dest_station){
		return(is_can_go[rv_dep_station][rv_dest_station]);
}
