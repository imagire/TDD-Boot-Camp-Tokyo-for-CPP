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
	EXPECT_TRUE(checkTrainRoute(YOKOHAMA,TOKYO));
	EXPECT_TRUE(checkTrainRoute(TOKYO,YOKOHAMA));
	EXPECT_TRUE(checkTrainRoute(TOKYO,OMIYA));
	EXPECT_TRUE(checkTrainRoute(OMIYA,TOKYO));

	EXPECT_TRUE(checkTrainRoute(OMIYA,YOKOHAMA));
	EXPECT_TRUE(checkTrainRoute(YOKOHAMA,OMIYA));


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
	gStationMap.insert(getPair(TOKYO));
}

bool checkTrainRoute(STATION station1, STATION station2)
{
	STATIONS stations;
	return checkTrainRoute(station1, station2, &stations);
}

bool checkTrainRoute(STATION station1, STATION station2, STATIONS * visitedStations)
{
	if(station1 == station2)
	{
		return false;
	}

	if(std::find(visitedStations->begin(), visitedStations->end(), station1)
		!= visitedStations->end())
	{
		return false;
	}
	STATIONS stations = gStationMap[station1];
	if(std::find(stations.begin(), stations.end(), station2)
		!= stations.end())
	{
		return true;
	}
	visitedStations->push_back(station1);
	for (STATIONS::iterator it= stations.begin();it != stations.end(); it++)
	{
		if (checkTrainRoute(*it, station2, visitedStations))
		{
			return true;
		}
	}

	return false;
}
