#include <gtest/gtest.h>
#include "path.h"

class PathTest : public ::testing::Test {
protected:
	virtual void SetUp()
	{
		path.AddReach("��{", "��Y�a");
		path.AddReach("��Y�a", "�ԉH");
		path.AddReach("��Y�a", "��������");
		path.AddReach("�ԉH", "�r��");
		path.AddReach("�ԉH", "�c�[");
		path.AddReach("�r��", "�V�h");
		path.AddReach("�r��", "�c�[");
		path.AddReach("�c�[", "�H�t��");
		path.AddReach("��������", "�V�h");
		path.AddReach("��������", "��������");
		path.AddReach("�V�h", "�a�J");
		path.AddReach("�V�h", "�����̐�");
		path.AddReach("�����̐�", "�H�t��");
		path.AddReach("�����̐�", "����");
		path.AddReach("�H�t��", "����");
		path.AddReach("�a�J", "����");
		path.AddReach("�a�J", "��������");
		path.AddReach("����", "���");
		path.AddReach("��������", "���");
		path.AddReach("��������", "���l");
		path.AddReach("���", "���l");
	}

	Path path;
};

TEST_F(PathTest, IsArrivalTestFromMinamiurawaToShibuya)
{
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("��Y�a", "�a�J", result));

	ASSERT_EQ(true, 2 <= result.size());
	EXPECT_EQ("��Y�a", result[0]);
	EXPECT_EQ("�a�J", result[result.size()-1]);

}

TEST_F(PathTest, IsArrivalTestChokutuu)
{
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("��{", "��Y�a", result));
	EXPECT_EQ(true, path.IsArrival("��Y�a", "��������", result));
	EXPECT_EQ(true, path.IsArrival("��Y�a", "�ԉH", result));
	EXPECT_EQ(true, path.IsArrival("�ԉH", "�r��", result));
	EXPECT_EQ(true, path.IsArrival("�r��", "�V�h", result));
	EXPECT_EQ(true, path.IsArrival("�r��", "�c�[", result));
}

TEST_F(PathTest, IsArrivalTestFromOomiyaToYokohama)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("��{", "���l", result));

	expected_root.push_back("��{");
	expected_root.push_back("����");
	expected_root.push_back("���l");

	// EXPECT_EQ(expected_root, result);

}

TEST_F(PathTest, IsArrivalTestFromYokohamaToOomiya)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(true, path.IsArrival("���l", "��{", result));

	expected_root.push_back("���l");
	expected_root.push_back("����");
	expected_root.push_back("��{");

	// EXPECT_EQ(expected_root, result);
}

TEST_F(PathTest, IsArrivalTestFromYokohamaToTokyo)
{
	Path::Root expected_root;
	Path::Root result;


	EXPECT_EQ(true, path.IsArrival("���l", "����", result));

	expected_root.push_back("���l");
	expected_root.push_back("����");

	// EXPECT_EQ(expected_root, result);
}

TEST_F(PathTest, IsArrivalTestFromYokohamaToOoshima)
{
	Path::Root expected_root;
	Path::Root result;

	EXPECT_EQ(false, path.IsArrival("���l", "�哇", result));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}
