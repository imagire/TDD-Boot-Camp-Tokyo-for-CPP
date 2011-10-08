#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

namespace st
{
	enum Station
	{
		Yokohama=0,
		Kawasaki,
		MusashiKosugi,
		Tokyo,
		Shibuya,
		NishiKokubunji,
		Shinjuku,
		Ochanomizu,
		Akihabara,
		Tabata,
		Ikebukuro,
		Akabane,
		MinamiUrawa,
		Ohshima,
		Ohmiya,
		StationEnd
	};
}

struct Path
{
	st::Station st1;
	st::Station st2;
	int	time;
}const good_paths[]=
{
	{st::Yokohama,st::Kawasaki,14},
	{st::Yokohama,st::MusashiKosugi,23},
	{st::Kawasaki,st::MusashiKosugi,19},
	{st::Kawasaki,st::Tokyo,24},
	{st::MusashiKosugi,st::Shibuya,21},
	{st::MusashiKosugi,st::NishiKokubunji,50},
	{st::Tokyo,st::Shibuya,25},
	{st::Tokyo,st::Akihabara,6},
	{st::Tokyo,st::Ochanomizu,10},
	{st::Shibuya,st::Shinjuku,10},
	{st::Akihabara,st::Ochanomizu,8},
	{st::Akihabara,st::Tabata,11},
	{st::Ochanomizu,st::Shinjuku,16},
	{st::Shinjuku,st::NishiKokubunji,32},
	{st::Shinjuku,st::Ikebukuro,11},
	{st::Tabata,st::Ikebukuro,12},
	{st::Tabata,st::Akabane,14},
	{st::Ikebukuro,st::Akabane,15},
	{st::NishiKokubunji,st::MinamiUrawa,36},
	{st::Akabane,st::MinamiUrawa,16},
	{st::MinamiUrawa,st::Ohmiya,12},
};

#define Elements(a) (sizeof(a)/sizeof(a[0]))

int path_stack[100];

bool is_reach(st::Station station1, st::Station station2 , int stack_position=0)
{
	for(int n=0;n<Elements(good_paths);n++)
	{
		if(good_paths[n].st1 == station1 && good_paths[n].st2 == station2)
			return true;
		if(good_paths[n].st2 == station1 && good_paths[n].st1 == station2)
			return true;

	}
	for(int n=0;n<Elements(good_paths);n++)
	{
		bool pass=false;
		for(int j=0;j<stack_position;j++)
		{
			if(path_stack[j] == n)
			{
				pass=true;
			}
		}
		if(pass)
		{
			continue;
		}

		if(good_paths[n].st1 == station1 )
		{
			path_stack[stack_position] = n;
			if(is_reach(good_paths[n].st2 , station2,stack_position + 1))
			{
				return true;
			}
			else
			{
				continue;
			}
		}
		if(good_paths[n].st2 == station1 )
		{
			path_stack[stack_position] = n;
			if(is_reach(good_paths[n].st1 , station2,stack_position + 1))
			{
				return true;
			}
			else
			{
				continue;
			}
		}
	}
	return false;
}

bool get_eta(st::Station station1, st::Station station2 ,int *reach_time, int stack_position=0,int now_time=0)
{
	for(int n=0;n<Elements(good_paths);n++)
	{
		// 隣駅か調べる
		if( (good_paths[n].st1 == station1 && good_paths[n].st2 == station2)
			|| (good_paths[n].st2 == station1 && good_paths[n].st1 == station2) )
		{
			*reach_time=now_time+good_paths[n].time;
			for(int j=0;j<stack_position;j++)
			{
				cout << "path[" << j << "] : " << path_stack[j] << endl;
			}
			return true;
		}

	}
	for(int n=0;n<Elements(good_paths);n++)
	{
		// すでに通ったか調べる
		bool pass=false;
		for(int j=0;j<stack_position;j++)
		{
			if(path_stack[j] == n)
			{
				pass=true;
			}
		}
		if(pass)
		{
			continue;
		}

		// 乗り換え出来るか調べる。
		if(good_paths[n].st1 == station1 )
		{
			path_stack[stack_position] = n;
			if(get_eta(good_paths[n].st2 , station2,reach_time,stack_position + 1,now_time+good_paths[n].time))
			{
				return true;
			}
			else
			{
				continue;
			}
		}
		if(good_paths[n].st2 == station1 )
		{
			path_stack[stack_position] = n;
			if(get_eta(good_paths[n].st1 , station2,reach_time,stack_position + 1,now_time+good_paths[n].time))
			{
				return true;
			}
			else
			{
				continue;
			}
		}
	}
	return false;
}

void get_weight(st::Station station1, st::Station station2 ,int *weight,int time=0)
{
	for(int n=0;n<Elements(good_paths);n++)
	{
		// 乗り換え出来るか調べる。
		st::Station tonari=st::StationEnd;
		if(good_paths[n].st1 == station1 )
		{
			tonari=good_paths[n].st2;
		}
		if(good_paths[n].st2 == station1 )
		{
			tonari=good_paths[n].st1;
		}

		if(st::StationEnd != tonari)
		{
			if(weight[tonari] > time + good_paths[n].time)
			{
				weight[tonari]=time + good_paths[n].time;
				get_weight(tonari,station2,weight,time + good_paths[n].time);
			}
		}
	}
}

bool weight_to_route(st::Station station1, st::Station station2 ,int *weight,vector<st::Station> &route, int now_time=0)
{
	// 乗り換え出来るか調べる。

	if(now_time > weight[station1] )
	{
		return false;
	}
	if(station1==station2){
		route.push_back(station2);
		return true;
	}
	route.push_back(station1);
	for(int n=0;n<Elements(good_paths);n++)
	{
		if(good_paths[n].st1 == station1 )
		{
			if(good_paths[n].st2 == station1)
				continue;
			if(weight_to_route(good_paths[n].st2,station2,weight,route,now_time + good_paths[n].time))
				return true;
		}
		if(good_paths[n].st2 == station1 )
		{
			if(good_paths[n].st1 == station1)
				continue;
			if(weight_to_route(good_paths[n].st1,station2,weight,route,now_time + good_paths[n].time))
				return true;
		}
	}
	route.pop_back();
	return false;
}

void get_short(st::Station station1, st::Station station2, vector<st::Station> &route)
{
	int weight[st::StationEnd];
	for(int i=0;i<st::StationEnd;i++)
		weight[i]=0x7fffffff;
	weight[station1]=0;
	get_weight(station1,station2,weight);
	weight_to_route(station1,station2,weight,route);
	for(int i=0;i<route.size();i++)
		cout<<route[i]<<endl;
}

TEST(AddTest, ForDebug)
{
	EXPECT_TRUE(is_reach(st::Yokohama,st::Ohmiya));
}

TEST(AddTest, Exchange)
{
	EXPECT_FALSE(is_reach(st::Yokohama,st::Ohshima));
	EXPECT_FALSE(is_reach(st::Ohshima,st::Yokohama));

	EXPECT_TRUE(is_reach(st::Yokohama,st::Ohmiya));
	EXPECT_TRUE(is_reach(st::Ohmiya,st::Yokohama));

	EXPECT_TRUE(is_reach(st::Yokohama,st::Tokyo));
	EXPECT_TRUE(is_reach(st::Tokyo,st::Yokohama));

	EXPECT_TRUE(is_reach(st::Tokyo,st::Ohmiya));
	EXPECT_TRUE(is_reach(st::Ohmiya,st::Tokyo));
}

TEST(AddTest, Route)
{
	EXPECT_TRUE(is_reach(st::Yokohama,st::Ikebukuro));
	EXPECT_TRUE(is_reach(st::Yokohama,st::Shibuya));
	EXPECT_TRUE(is_reach(st::MusashiKosugi,st::Akihabara));
	EXPECT_TRUE(is_reach(st::Shinjuku,st::Ohmiya));
	EXPECT_TRUE(is_reach(st::Tokyo,st::Ikebukuro));
	EXPECT_TRUE(is_reach(st::Yokohama,st::Ohmiya));
}

TEST(AddTest, Time)
{
	int eta=0;
	EXPECT_TRUE(get_eta(st::Yokohama,st::Ohmiya,&eta));
	EXPECT_LE(97,eta);
	cout << "Yokohama->Ohmiya:" << eta << endl;
	EXPECT_TRUE(get_eta(st::MusashiKosugi,st::Tabata,&eta));
	EXPECT_LE(60,eta);
	cout << "MusashiKosugi->Tabata:" << eta << endl;
	EXPECT_TRUE(get_eta(st::Shibuya,st::Akihabara,&eta));
	EXPECT_LE(31,eta);
	cout << "Shibuya->Akihabara:" << eta << endl;
	EXPECT_TRUE(get_eta(st::Kawasaki,st::Tokyo,&eta));
	EXPECT_LE(24,eta);
	cout << "川崎⇒東京:" << eta << endl;
}

TEST(AddTest, Short)
{
	std::vector<st::Station> route;
	get_short(st::Yokohama,st::Ohmiya,route);
	std::vector<st::Station> yokohama_to_ohmiya;
	yokohama_to_ohmiya.push_back(st::Yokohama);
	yokohama_to_ohmiya.push_back(st::Kawasaki);
	yokohama_to_ohmiya.push_back(st::Tokyo);
	yokohama_to_ohmiya.push_back(st::Akihabara);
	yokohama_to_ohmiya.push_back(st::Tabata);
	yokohama_to_ohmiya.push_back(st::Akabane);
	yokohama_to_ohmiya.push_back(st::MinamiUrawa);
	yokohama_to_ohmiya.push_back(st::Ohmiya);
	EXPECT_EQ(yokohama_to_ohmiya, route);

	route.clear();
	get_short(st::NishiKokubunji, st::Tokyo,route);
	std::vector<st::Station> nishikokubunji_to_tokyo;
	nishikokubunji_to_tokyo.push_back(st::NishiKokubunji);
	nishikokubunji_to_tokyo.push_back(st::Shinjuku);
	nishikokubunji_to_tokyo.push_back(st::Ochanomizu);
	nishikokubunji_to_tokyo.push_back(st::Tokyo);
	EXPECT_EQ(nishikokubunji_to_tokyo, route);

	route.clear();
	get_short(st::Ikebukuro, st::Kawasaki,route);
	std::vector<st::Station> ikebukuro_to_kawasaki;
	ikebukuro_to_kawasaki.push_back(st::Ikebukuro);
	ikebukuro_to_kawasaki.push_back(st::Tabata);
	ikebukuro_to_kawasaki.push_back(st::Akihabara);
	ikebukuro_to_kawasaki.push_back(st::Tokyo);
	ikebukuro_to_kawasaki.push_back(st::Kawasaki);
	EXPECT_EQ(ikebukuro_to_kawasaki, route);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

