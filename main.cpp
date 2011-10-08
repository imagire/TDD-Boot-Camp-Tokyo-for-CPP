#include <gtest/gtest.h>
#include <list>

bool canGo(const std::string& source, const std::string& destination)
{
	if ("Ohmiya" == source && "Yokohama" == destination)
	{
		return true;
	}

	if ("Yokohama" == source)
	{
		if ("Tokyo" == destination || "Ohmiya" == destination)
		{
			return true;
		}
		return false;
	}

	if ("Tokyo" == source)
	{
		if ("Yokohama" == destination || "Ohmiya" == destination)
		{
			return true;
		}
		return false;
	}

	if ("Ohmiya" == source)
	{
		if ("Yokohama" == destination || "Tokyo" == destination)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool canGoWithList(const std::list<std::string>& sourceToDestination)
{


	return false;
}

TEST(canGoTest, Test1)
{
	EXPECT_TRUE(canGo("Ohmiya", "Yokohama"));
	EXPECT_TRUE(canGo("Yokohama", "Tokyo"));
	EXPECT_TRUE(canGo("Tokyo", "Yokohama"));
	EXPECT_TRUE(canGo("Tokyo", "Ohmiya"));
	EXPECT_TRUE(canGo("Ohmiya", "Tokyo"));

	EXPECT_FALSE(canGo("Yokohama", "OhShima"));
}

TEST(canGoTest, Test2)
{
	std::list<std::string> testData1;
	testData1.push_back("Yokohama");
	EXPECT_FALSE(canGoWithList(testData1));
	testData1.push_back("Tokyo");
	EXPECT_TRUE(canGoWithList(testData1));
	testData1.push_back("Ohmiya");
	EXPECT_TRUE(canGoWithList(testData1));

	EXPECT_TRUE(canGoWithList(testData1));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
