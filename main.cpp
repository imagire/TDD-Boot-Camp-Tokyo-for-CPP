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
bool ashiato[ENUM_STATION_SIZE] = {false};

void initAshiato(void){
	for(int i = 0; i < ENUM_STATION_SIZE; i++) ashiato[i] = false;
}
void setUp(void){
		initAshiato();

		nextStation[OOMIYA][YOKOHAMA] = 1;
		nextStation[YOKOHAMA][OOMIYA] = 1;
		nextStation[OOMIYA][TOKYO] = 1;
		nextStation[TOKYO][OOMIYA] = 1;
		nextStation[OOMIYA][MINAMIURAWA] = 1;
		nextStation[MINAMIURAWA][OOMIYA] = 1;
		nextStation[MINAMIURAWA][AKABANE] = 1;
		nextStation[MINAMIURAWA][NISHIKOKUBUNJI] = 1;
		nextStation[AKABANE][MINAMIURAWA] = 1;
		nextStation[AKABANE][IKEBUKURO] = 1;
		nextStation[AKABANE][TABATA] = 1;
		nextStation[NISHIKOKUBUNJI][MINAMIURAWA] = 1;
		nextStation[NISHIKOKUBUNJI][SHINJUKU] = 1;
		nextStation[NISHIKOKUBUNJI][MUSASHIKOSUGI] = 1;
		nextStation[IKEBUKURO][AKABANE] = 1;
		nextStation[IKEBUKURO][SHINJUKU] = 1;
		nextStation[IKEBUKURO][TABATA] = 1;
		nextStation[TABATA][AKABANE] = 1;
		nextStation[TABATA][IKEBUKURO] = 1;
		nextStation[TABATA][AKIHABARA] = 1;
		nextStation[SHINJUKU][IKEBUKURO] = 1;
		nextStation[SHINJUKU][NISHIKOKUBUNJI] = 1;
		nextStation[SHINJUKU][OCHANOMIZU] = 1;
		nextStation[SHINJUKU][SHIBUYA] = 1;
		nextStation[OCHANOMIZU][SHINJUKU] = 1;
		nextStation[OCHANOMIZU][AKIHABARA] = 1;
		nextStation[OCHANOMIZU][TOKYO] = 1;
		nextStation[AKIHABARA][TOKYO] = 1;
		nextStation[AKIHABARA][OCHANOMIZU] = 1;
		nextStation[AKIHABARA][TABATA] = 1;
		nextStation[SHIBUYA][SHINJUKU] = 1;
		nextStation[SHIBUYA][TOKYO] = 1;
		nextStation[SHIBUYA][MUSASHIKOSUGI] = 1;
		nextStation[TOKYO][KAWASAKI] = 1;
		nextStation[TOKYO][SHIBUYA] = 1;
		nextStation[TOKYO][AKIHABARA] = 1;
		nextStation[TOKYO][OCHANOMIZU] = 1;
		nextStation[MUSASHIKOSUGI][SHIBUYA] = 1;
		nextStation[MUSASHIKOSUGI][KAWASAKI] = 1;
		nextStation[MUSASHIKOSUGI][NISHIKOKUBUNJI] = 1;
		nextStation[MUSASHIKOSUGI][YOKOHAMA] = 1;
		nextStation[KAWASAKI][MUSASHIKOSUGI] = 1;
		nextStation[KAWASAKI][TOKYO] = 1;
		nextStation[KAWASAKI][YOKOHAMA] = 1;
		nextStation[YOKOHAMA][KAWASAKI] = 1;
		nextStation[YOKOHAMA][MUSASHIKOSUGI] = 1;		
}

class Train {
public:
	Train () {setUp();};
	bool able(int from, int to) {
		bool result = false;
		ashiato[from] = true;
		for(int i= 0; i < ENUM_STATION_SIZE; i++){
			if(nextStation[from][i] == 1){
				if(i == to) {
					result = true;
					break;
				}
				else{
					if(ashiato[i] == false)
					{
						result = able(i, to);
						if (result == true)
						{
							break;
						}
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

	EXPECT_TRUE(train.able(OOMIYA, YOKOHAMA));
	initAshiato();
	EXPECT_FALSE(train.able(YOKOHAMA, OOSHIMA));
}

TEST(TrainTest, Test2)
{
	Train train;

	EXPECT_TRUE(train.able(YOKOHAMA, TOKYO));
	initAshiato();
	EXPECT_TRUE(train.able(TOKYO, OOMIYA));
	initAshiato();
	EXPECT_TRUE(train.able(TOKYO, YOKOHAMA));
	initAshiato();
	EXPECT_TRUE(train.able(OOMIYA, TOKYO));
}

TEST(TrainTest, Test3)
{
	Train train;
	EXPECT_TRUE(train.able(OOMIYA, YOKOHAMA));
}

TEST(TrainTest, TestManyStaion)
{
	Train train;
	for(int i=0; i<ENUM_STATION_SIZE; i++){
		initAshiato();
		if(i == OOSHIMA){
			EXPECT_FALSE(train.able(AKABANE, i));
		}
		else if(i != KAWASAKI){
			EXPECT_TRUE(train.able(KAWASAKI, i));
		}
	}
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
