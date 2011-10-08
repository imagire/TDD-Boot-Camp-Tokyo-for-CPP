#include <gtest/gtest.h>

#include <algorithm>
#include <map>


typedef enum {
	AKABANE,
	AKIHABARA,
	IKEBUKURO,
	KAWASAKI,
	MINAMIURAWA,
	MUSASHIKOSUGI,
	NISHIKOKUBUNJI,
	OCHANOMIZU,
	OMIYA,
	OSHIMA,
	SHIBUYA,
	SHINJUKU,
	TABATA,
	TOKYO,
	YOKOHAMA,

	STATION_COUNT
} STATION;

typedef std::vector<STATION> STATIONS;
typedef std::map<STATION, STATIONS> STATION_MAP;
STATION_MAP gStationMap;

extern void InitializeMap();

extern bool checkTrainRoute(STATION station1, STATION station2);
extern bool checkTrainRoute(STATION station1, STATION station2, STATIONS * visitedStations);

TEST(checkTrainRouteTest, 大島以外の駅は全部到達できるテスト)
{
	for(int i=0; i<STATION_COUNT; i++)
	{
		for(int j=0; j<STATION_COUNT; j++)
		{
			STATION st1 = static_cast<STATION>(i);
			STATION st2 = static_cast<STATION>(j);
			if(((st1 == OSHIMA) || (st2 == OSHIMA)) ||
				(st1 == st2))
			{
				continue;
			}
			EXPECT_TRUE(checkTrainRoute(st1, st2));
		}
	}
}

TEST(checkTrainRouteTest, 大島は到達できないテスト)
{
	EXPECT_FALSE(checkTrainRoute(OSHIMA,YOKOHAMA));
	EXPECT_FALSE(checkTrainRoute(YOKOHAMA,OSHIMA));
}

TEST(checkTrainRouteTest, 自分自身はNGとするテスト)
{
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
	case AKABANE :	
		neighbors.push_back(MINAMIURAWA);
		neighbors.push_back(IKEBUKURO);
		neighbors.push_back(TABATA);
		break;
	case AKIHABARA :	
		neighbors.push_back(TABATA);
		neighbors.push_back(OCHANOMIZU);
		neighbors.push_back(TOKYO);
		break;
	case IKEBUKURO :	
		neighbors.push_back(AKABANE);
		neighbors.push_back(TABATA);
		neighbors.push_back(SHINJUKU);
		break;
	case KAWASAKI :	
		neighbors.push_back(TOKYO);
		neighbors.push_back(MUSASHIKOSUGI);
		neighbors.push_back(YOKOHAMA);
		break;
	case MINAMIURAWA :	
		neighbors.push_back(OMIYA);
		neighbors.push_back(AKABANE);
		neighbors.push_back(NISHIKOKUBUNJI);
		break;
	case MUSASHIKOSUGI :	
		neighbors.push_back(NISHIKOKUBUNJI);
		neighbors.push_back(KAWASAKI);
		neighbors.push_back(YOKOHAMA);
		break;
	case NISHIKOKUBUNJI :	
		neighbors.push_back(MINAMIURAWA);
		neighbors.push_back(SHINJUKU);
		neighbors.push_back(MUSASHIKOSUGI);
		break;
	case OCHANOMIZU :	
		neighbors.push_back(SHINJUKU);
		neighbors.push_back(AKIHABARA);
		neighbors.push_back(TOKYO);
		break;
	case OMIYA :	
		neighbors.push_back(MINAMIURAWA);
		break;
	case OSHIMA :	
		break;
	case SHIBUYA :	
		neighbors.push_back(SHINJUKU);
		neighbors.push_back(TOKYO);
		neighbors.push_back(MUSASHIKOSUGI);
		break;
	case SHINJUKU :	
		neighbors.push_back(IKEBUKURO);
		neighbors.push_back(OCHANOMIZU);
		neighbors.push_back(SHIBUYA);
		neighbors.push_back(NISHIKOKUBUNJI);
		break;
	case TABATA :	
		neighbors.push_back(AKABANE);
		neighbors.push_back(IKEBUKURO);
		neighbors.push_back(AKIHABARA);
		break;
	case TOKYO :	
		neighbors.push_back(AKIHABARA);
		neighbors.push_back(OCHANOMIZU);
		neighbors.push_back(SHIBUYA);
		neighbors.push_back(KAWASAKI);
		break;
	case YOKOHAMA :	
		neighbors.push_back(KAWASAKI);
		neighbors.push_back(MUSASHIKOSUGI);
		break;
	}
	return std::pair<STATION, STATIONS>(st, neighbors);
}

void InitializeMap()
{
	gStationMap.insert(getPair(AKABANE));
	gStationMap.insert(getPair(AKIHABARA));
	gStationMap.insert(getPair(IKEBUKURO));
	gStationMap.insert(getPair(KAWASAKI));
	gStationMap.insert(getPair(MINAMIURAWA));
	gStationMap.insert(getPair(MUSASHIKOSUGI));
	gStationMap.insert(getPair(NISHIKOKUBUNJI));
	gStationMap.insert(getPair(OCHANOMIZU));
	gStationMap.insert(getPair(OMIYA));
	gStationMap.insert(getPair(OSHIMA));
	gStationMap.insert(getPair(SHIBUYA));
	gStationMap.insert(getPair(SHINJUKU));
	gStationMap.insert(getPair(TABATA));
	gStationMap.insert(getPair(TOKYO));
	gStationMap.insert(getPair(YOKOHAMA));

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
