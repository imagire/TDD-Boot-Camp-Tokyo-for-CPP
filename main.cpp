#include <gtest/gtest.h>

enum Station
{
	Station_Yokohama,
	Station_Ohshima,
	Station_Ohmiya,
	Station_Tokyo
};

struct Path
{
	Station st1;
	Station st2;
}const good_paths[]=
{
	{Station_Tokyo,Station_Yokohama},
	{Station_Tokyo,Station_Ohmiya},
};

#define Elements(a) (sizeof(a)/sizeof(a[0]))

int path_stack[100];

bool is_reach(Station station1, Station station2 , int stack_position=0)
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
			return is_reach(good_paths[n].st2 , station2,stack_position + 1);
		}
		if(good_paths[n].st2 == station1 )
		{
			path_stack[stack_position] = n;
			return is_reach(good_paths[n].st1 , station2,stack_position + 1);
		}

	}
	return false;
}

TEST(AddTest, ForDebug)
{
	EXPECT_TRUE(is_reach(Station_Yokohama,Station_Ohmiya));
}

TEST(AddTest, Exchange)
{
	EXPECT_FALSE(is_reach(Station_Yokohama,Station_Ohshima));
	EXPECT_FALSE(is_reach(Station_Ohshima,Station_Yokohama));

	EXPECT_TRUE(is_reach(Station_Yokohama,Station_Ohmiya));
	EXPECT_TRUE(is_reach(Station_Ohmiya,Station_Yokohama));

	EXPECT_TRUE(is_reach(Station_Yokohama,Station_Tokyo));
	EXPECT_TRUE(is_reach(Station_Tokyo,Station_Yokohama));

	EXPECT_TRUE(is_reach(Station_Tokyo,Station_Ohmiya));
	EXPECT_TRUE(is_reach(Station_Ohmiya,Station_Tokyo));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}

