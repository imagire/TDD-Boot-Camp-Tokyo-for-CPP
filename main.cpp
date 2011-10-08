#include <gtest/gtest.h>

namespace st
{
	enum Station
	{
		Yokohama,
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
	};
}

struct Path
{
	st::Station st1;
	st::Station st2;
}const good_paths[]=
{
	{st::Yokohama,st::Kawasaki},
	{st::Yokohama,st::MusashiKosugi},
	{st::Kawasaki,st::MusashiKosugi},
	{st::Kawasaki,st::Tokyo},
	{st::MusashiKosugi,st::Shibuya},
	{st::MusashiKosugi,st::NishiKokubunji},
	{st::Tokyo,st::Shibuya},
	{st::Tokyo,st::Akihabara},
	{st::Tokyo,st::Ochanomizu},
	{st::Shibuya,st::Shinjuku},
	{st::Akihabara,st::Ochanomizu},
	{st::Akihabara,st::Tabata},
	{st::Ochanomizu,st::Shinjuku},
	{st::Shinjuku,st::NishiKokubunji},
	{st::Shinjuku,st::Ikebukuro},
	{st::Tabata,st::Ikebukuro},
	{st::Tabata,st::Akabane},
	{st::Ikebukuro,st::Akabane},
	{st::NishiKokubunji,st::MinamiUrawa},
	{st::Akabane,st::MinamiUrawa},
	{st::MinamiUrawa,st::Ohmiya},
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

}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

