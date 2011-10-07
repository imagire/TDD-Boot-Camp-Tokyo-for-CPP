#include <gtest/gtest.h>

class Norikae{
public:
	enum Station{
		YOKOHAMA,
		OOMIYA,
		OHSHIMA,

		END
	};

private:
	struct Edge{
		Station st1;
		Station st2;
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
	{Norikae::OOMIYA, Norikae::YOKOHAMA},
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
