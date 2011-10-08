#include <gtest/gtest.h>

#include <algorithm>
#include <map>


typedef enum {
	OMIYA,
	YOKOHAMA,
	OSHIMA,
	TOKYO
} STATION;

typedef std::vector<STATION> STATIONS;
typedef std::map<STATION, STATIONS> STATION_MAP;
STATION_MAP gStationMap;

extern void InitializeMap();

extern bool checkTrainRoute(STATION station1, STATION station2);
extern bool checkTrainRoute(STATION station1, STATION station2, STATIONS * visitedStations);

TEST(checkTrainRouteTest, Test1)
{
	EXPECT_TRUE(checkTrainRoute(OMIYA,YOKOHAMA));
	EXPECT_TRUE(checkTrainRoute(YOKOHAMA,OMIYA));

	EXPECT_TRUE(checkTrainRoute(YOKOHAMA,TOKYO));
	EXPECT_TRUE(checkTrainRoute(TOKYO,YOKOHAMA));

	EXPECT_TRUE(checkTrainRoute(TOKYO,OMIYA));
	EXPECT_TRUE(checkTrainRoute(OMIYA,TOKYO));
}

TEST(checkTrainRouteTest, Test2)
{
	EXPECT_FALSE(checkTrainRoute(OSHIMA,YOKOHAMA));
	EXPECT_FALSE(checkTrainRoute(YOKOHAMA,OSHIMA));
	EXPECT_FALSE(checkTrainRoute(OMIYA,OMIYA));
	EXPECT_FALSE(checkTrainRoute(YOKOHAMA,YOKOHAMA));
	EXPECT_FALSE(checkTrainRoute(OSHIMA,OSHIMA));
}


int main(int argc, char* argv[])
{
	InitializeMap();

    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}


std::pair<STATION, STATIONS> getPair(STATION st)
{
	STATIONS neighbors;
	switch(st)
	{
	case YOKOHAMA :
		neighbors.push_back(TOKYO);
		break;
	case OMIYA :
		neighbors.push_back(TOKYO);
		break;
	case OSHIMA :
		break;
	case TOKYO :
		neighbors.push_back(YOKOHAMA);
		neighbors.push_back(OMIYA);
		break;
	default :
		break;
	}
	return std::pair<STATION, STATIONS>(st, neighbors);
}

void InitializeMap()
{
	gStationMap.insert(getPair(YOKOHAMA));
	gStationMap.insert(getPair(OMIYA));
	gStationMap.insert(getPair(OSHIMA));
}

bool checkTrainRoute(STATION station1, STATION station2)
{
	STATIONS stations;
	return checkTrainRoute(station1, station2, &stations);
}

bool checkTrainRoute(STATION station1, STATION station2, STATIONS * visitedStations)
{
	STATIONS stations = gStationMap[station1];
	if(std::find(stations.begin(), stations.end(), station2)
		!= stations.end())
	{
		return true;
	}

	return false;
}
