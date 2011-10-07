#include <gtest/gtest.h>

class Norikae{
public:
	enum Station{
		OOMIYA,
		MINAMIURAWA,
		AKABANE,
		IKEBUKURO,
		TABATA,
		SHINJYUKU,
		OCYANOMIZU,
		AKIHABARA,
		NISHIKOKUBUNNJI,
		SHIBUYA,
		TOKYO,
		MUSASHIKOSUGI,
		KAWASAKI,
		YOKOHAMA,
		OHSHIMA,

		END
	};

private:
	struct Edge{
		Station st1;
		Station st2;
		unsigned int time;
		float distance;
	};

	static const Edge aEdge[];

public:
	Norikae(){}
	~Norikae(){}

	static bool IsConnected(Station from, Station to)
	{
		const Edge *p = aEdge;

		while(p->st1 != END){
			if(p->st1 == from && p->st2 == to) return true;
			if(p->st2 == from && p->st1 == to) return true;
			p++;
		}

		return false;
	}
};

const Norikae::Edge Norikae::aEdge[] = {
	{Norikae::OOMIYA, Norikae::MINAMIURAWA, 12, 7.8f},
	{Norikae::MINAMIURAWA, Norikae::AKABANE, 16, 9.3f},
	{Norikae::MINAMIURAWA, Norikae::NISHIKOKUBUNNJI, 36, 27.8f},
	{Norikae::AKABANE, Norikae::IKEBUKURO, 15, 5.5f},
	{Norikae::AKABANE, Norikae::TABATA, 14, 6.1f},
	{Norikae::IKEBUKURO, Norikae::TABATA, 12, 5.2f},
	{Norikae::IKEBUKURO, Norikae::SHINJYUKU, 11, 4.8f},
	{Norikae::TABATA, Norikae::AKIHABARA, 11, 5.1f},
	{Norikae::SHINJYUKU, Norikae::NISHIKOKUBUNNJI, 32, 22.5f},
	{Norikae::SHINJYUKU, Norikae::SHIBUYA, 10, 3.4f},
	{Norikae::SHINJYUKU, Norikae::OCYANOMIZU, 16, 7.7f},
	{Norikae::OCYANOMIZU, Norikae::AKIHABARA, 8, 0.9f},
	{Norikae::OCYANOMIZU, Norikae::TOKYO, 10, 2.6f},
	{Norikae::AKIHABARA, Norikae::TOKYO, 6, 2.0f},
	{Norikae::NISHIKOKUBUNNJI, Norikae::MUSASHIKOSUGI, 50, 24.3f},
	{Norikae::SHIBUYA, Norikae::TOKYO, 25, 14.0f},
	{Norikae::SHIBUYA, Norikae::MUSASHIKOSUGI, 21, 10.8f},
	{Norikae::TOKYO, Norikae::KAWASAKI, 24, 18.2f},
	{Norikae::MUSASHIKOSUGI, Norikae::KAWASAKI, 19, 7.5f},
	{Norikae::MUSASHIKOSUGI, Norikae::YOKOHAMA, 23, 13.4f},
	{Norikae::KAWASAKI, Norikae::YOKOHAMA, 14, 10.6f},
	{Norikae::END, Norikae::END},
};


TEST(NorikaeTest1, IsConnected)
{
	EXPECT_EQ(true, Norikae::IsConnected(Norikae::OOMIYA, Norikae::YOKOHAMA));
	EXPECT_EQ(false, Norikae::IsConnected(Norikae::OOMIYA, Norikae::OHSHIMA));
	EXPECT_EQ(false, Norikae::IsConnected(Norikae::YOKOHAMA, Norikae::OHSHIMA));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
