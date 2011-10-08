#include <gtest/gtest.h>
#include <list>
#include <map>

namespace
{
	enum Station
	{
		Ohmiya,
		Yokohama,
		Tokyo,
		MusashiKosugi,
		Kawasaki,
		Shibuya,
		NishiKokubunji,
		Shinjuku,
		Ochanomizu,
		Akihabara,
		Ikebukuro,
		Tabata,
		Akabane,
		Minamiurawa,

		Ohshima
	};
}

const int MAXIMUM_TRANSRATION(10);

struct StationInformation
{
	Station first;
	Station second;
	int time;
};

StationInformation createStationInformation(const Station first, const Station second, const int time)
{
	struct StationInformation data = {first, second, time};
	return data;
}

std::list<Station> calculateMinimumRoute(const Station source, const Station destination)
{

	return std::list<Station>();
}

bool canGo(const Station source, const Station destination, int& time, int translationCount = 0)
{
	if (translationCount > MAXIMUM_TRANSRATION)
	{
		return false;
	}

	static std::vector<StationInformation> connectionAdminission;
	if (connectionAdminission.empty())
	{
		connectionAdminission.push_back(createStationInformation(Yokohama, Kawasaki, 14));
		connectionAdminission.push_back(createStationInformation(Yokohama, MusashiKosugi, 23));
		connectionAdminission.push_back(createStationInformation(Kawasaki, MusashiKosugi, 19));
		connectionAdminission.push_back(createStationInformation(Kawasaki, Tokyo, 24));
		connectionAdminission.push_back(createStationInformation(MusashiKosugi, Shibuya, 21));
		connectionAdminission.push_back(createStationInformation(MusashiKosugi, NishiKokubunji, 50));
		connectionAdminission.push_back(createStationInformation(Tokyo, Shibuya, 25));
		connectionAdminission.push_back(createStationInformation(Tokyo, Ochanomizu, 10));
		connectionAdminission.push_back(createStationInformation(Tokyo, Akihabara, 6));
		connectionAdminission.push_back(createStationInformation(Ochanomizu, Shinjuku, 16));
		connectionAdminission.push_back(createStationInformation(Shibuya, Shinjuku, 10));
		connectionAdminission.push_back(createStationInformation(Ikebukuro, Shinjuku, 11));
		connectionAdminission.push_back(createStationInformation(Akihabara, Ochanomizu, 8));
		connectionAdminission.push_back(createStationInformation(Akihabara, Tabata, 11));
		connectionAdminission.push_back(createStationInformation(Tabata, Ikebukuro, 12));
		connectionAdminission.push_back(createStationInformation(Tabata, Akabane, 14));
		connectionAdminission.push_back(createStationInformation(Akabane, Ikebukuro, 15));
		connectionAdminission.push_back(createStationInformation(Akabane, Minamiurawa, 16));
		connectionAdminission.push_back(createStationInformation(Minamiurawa, NishiKokubunji, 36));
		connectionAdminission.push_back(createStationInformation(Shinjuku, NishiKokubunji, 32));
		connectionAdminission.push_back(createStationInformation(Minamiurawa, Ohmiya, 12));
	}
	
	std::vector<Station> recursiveList;
	for (unsigned int i = 0; i < connectionAdminission.size(); ++i)
	{
		if (source == connectionAdminission.at(i).first)
	    {
			if (destination == connectionAdminission.at(i).second)
			{
				time += connectionAdminission.at(i).time;
				std::cout << destination;
				return true;
			}
			else
			{
				recursiveList.push_back(connectionAdminission.at(i).second);
			}
		}
		if (source == connectionAdminission.at(i).second)
		{
			if (destination == connectionAdminission.at(i).first)
			{
				time += connectionAdminission.at(i).time;
				std::cout << destination;
				return true;
			}
			else
			{
				recursiveList.push_back(connectionAdminission.at(i).first);
			}
		}
	}

	bool returnCode(false);
	if (!recursiveList.empty())
	{
		for (unsigned int i = 0; i < recursiveList.size() ; ++i)
		{
			if (true == canGo(recursiveList.at(i), destination, time, ++translationCount))
			{
				returnCode = true;
			}
		}
	}

	return returnCode;
}

TEST(canGoTest, TestMain)
{
	int time = 0;
	EXPECT_TRUE(canGo(Ohmiya, Yokohama, time));
	EXPECT_TRUE(canGo(Yokohama, Tokyo, time));
	EXPECT_TRUE(canGo(Tokyo, Yokohama, time));
	EXPECT_TRUE(canGo(Tokyo, Ohmiya, time));
	EXPECT_TRUE(canGo(Ohmiya, Tokyo, time));

	EXPECT_FALSE(canGo(Yokohama, Ohshima, time));
}

TEST(canGoTest, ManyStation)
{
	int time = 0;
	EXPECT_TRUE(canGo(Ohmiya, Yokohama, time));
	EXPECT_TRUE(canGo(Yokohama, Shinjuku, time));
	EXPECT_TRUE(canGo(Yokohama, Ohmiya, time));
	EXPECT_TRUE(canGo(MusashiKosugi, Ikebukuro, time));
	EXPECT_TRUE(canGo(Kawasaki, Akabane, time));
}

TEST(canGoTest, testOutputTime)
{
	int time = 0;
	EXPECT_TRUE(canGo(Yokohama, Kawasaki, time));
	EXPECT_EQ(time, 14);

	time = 0;
	EXPECT_TRUE(canGo(Yokohama, Kawasaki, time));
	EXPECT_TRUE(canGo(Kawasaki, Tokyo, time));
	EXPECT_EQ(time, 38);

	time = 0;
	EXPECT_TRUE(canGo(Yokohama, Kawasaki, time)); // 14
	EXPECT_TRUE(canGo(Kawasaki, Tokyo, time));  // 24
	EXPECT_TRUE(canGo(Tokyo, Shibuya, time)); // 25
	EXPECT_EQ(time, 63);
	EXPECT_TRUE(canGo(Shibuya, Shinjuku, time)); // 10
	EXPECT_EQ(time, 73);
	EXPECT_TRUE(canGo(Shinjuku, Ikebukuro, time)); // 11
	EXPECT_EQ(time, 84);
	EXPECT_TRUE(canGo(Ikebukuro, Akabane, time));  // 15
	EXPECT_EQ(time, 99);
	EXPECT_TRUE(canGo(Akabane, Minamiurawa, time)); // 16
	EXPECT_EQ(time, 115);
	EXPECT_TRUE(canGo(Minamiurawa, Ohmiya, time)); // 12
	EXPECT_EQ(time, 127);
}

TEST(calculate, testCalc)
{
	std::list<Station> result;
	result = calculateMinimumRoute(Yokohama, Kawasaki);
	std::list<Station> expectedResult;
	expectedResult.push_back(Yokohama);
	expectedResult.push_back(Kawasaki);
	EXPECT_TRUE(!result.empty());
	EXPECT_EQ(result, expectedResult);

	result = calculateMinimumRoute(Yokohama, Shibuya);
	expectedResult.clear();
	expectedResult.push_back(Yokohama);
	expectedResult.push_back(MusashiKosugi);
	expectedResult.push_back(Shibuya);
	EXPECT_TRUE(!result.empty());
	EXPECT_EQ(result, expectedResult);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
