#include <gtest/gtest.h>

enum {
	OOMIYA=0, 
	YOKOHAMA,
	OOSHIMA,
	TOKYO,
	AKABANE, 
	KAWASAKI,
	MUSASHIKOSUGI,
	SHIBUYA,
	NISHIKOKUBUNJI,
	SHINJUKU,
	OCHANOMIZU,
	AKIHABARA,
	IKEBUKURO,
	TABATA,
	MINAMIURAWA,
	ENUM_STATION_SIZE
};

int nextStation[ENUM_STATION_SIZE][ENUM_STATION_SIZE] = {0};

bool ashiato[ENUM_STATION_SIZE][ENUM_STATION_SIZE] = {false};

class Train {
public:
	Train () {};
	bool able(int from, int to) {
		bool result = false;
		nextStation[OOMIYA][YOKOHAMA] = 1;
		nextStation[YOKOHAMA][OOMIYA] = 1;
		nextStation[YOKOHAMA][OOSHIMA] = 0;
		nextStation[YOKOHAMA][TOKYO] = 1;
		nextStation[TOKYO][OOMIYA] = 1;
		nextStation[TOKYO][YOKOHAMA] = 1;
		nextStation[OOMIYA][TOKYO] = 1;
		nextStation[AKIHABARA][KAWASAKI] = 1;
		nextStation[KAWASAKI][TOKYO] = 1;
		nextStation[KAWASAKI][AKIHABARA] = 1;
		nextStation[TOKYO][KAWASAKI] = 1;
		nextStation[AKIHABARA][KAWASAKI] = 1;

		for(int i= 0; i < ENUM_STATION_SIZE; i++){
			ashiato[from][i] = true;
			if(nextStation[from][i] == 1){
				if(i == to) {
					result = true;
					break;
				}
				else{
					if(ashiato[from][i] == false)
					{
					result = able(i, to);
					}
				}
			}
		}
		return result;
	}
	bool checkTokyo(int from) {
		return able(from, TOKYO);
	}
};

TEST(TrainTest, Test1)
{
	Train train;

//	EXPECT_TRUE(train.able(OOMIYA, YOKOHAMA));
	EXPECT_FALSE(train.able(YOKOHAMA, OOSHIMA));
}

TEST(TrainTest, Test2)
{
	Train train;

	EXPECT_TRUE(train.able(YOKOHAMA, TOKYO));
	EXPECT_TRUE(train.able(TOKYO, OOMIYA));
	EXPECT_TRUE(train.able(TOKYO, YOKOHAMA));
	EXPECT_TRUE(train.able(OOMIYA, TOKYO));
}

TEST(TrainTest, Test3)
{
	Train train;
	EXPECT_TRUE(train.able(OOMIYA, YOKOHAMA));

//EXPECT_TRUE(train.checkTokyo(OOMIYA) && train.checkTokyo(YOKOHAMA));
}

TEST(TrainTest, TestManyStaion)
{
	Train train;
	EXPECT_TRUE(train.able(KAWASAKI, AKIHABARA));
	EXPECT_TRUE(train.able(AKABANE, KAWASAKI));
	
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
