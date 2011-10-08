#include <gtest/gtest.h>
#include <string>
#include <map>

using std::string;
using std::pair;
using std::map;
using std::make_pair;

struct �w {
    const string �w��;

    �w(string �w��) : �w��(�w��) {}
    static �w* �擾(string �w��);

    bool operator<(const �w& �w) const {
        return �w.�w�� < �w��;
    }
};

�w �S�w[] = {
    �w("�哇"),
    �w("���l"),
    �w("��{"),
    �w("����"),
    �w("��Y�a"),
    �w("�ԉH"),
    �w("�r��"),
    �w("�c�["),
    �w("��������"),
    �w("�V�h"),
    �w("�䒃�m��"),
    �w("�H�t��"),
    �w("�a�J"),
    �w("��������"),
    �w("���"),
};

�w* �w::�擾(string �w��) {
    for (int i = 0; i < _countof(�S�w); i++) {
        if (�S�w[i].�w�� == �w��) {
            return &�S�w[i];
        }
    }
    return NULL;
}


map<pair<�w, �w>, int> �S��;

void �ړ����Ԃ�ݒ肷��() {
    �S��[make_pair(*�w::�擾("�V�h"), *�w::�擾("��������"))] = 32;
/*
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    �S��[make_pair(�w::�擾("�V�h"), �w::�擾("�V�h"))] = 0;
    */
    }

bool �s���邩�Ȏ���(�w �o���w, �w �ړI�w) 
{
    if (�o���w.�w�� == "�哇" || �ړI�w.�w�� == "�哇") {
        return false;
    }
    return true;
}

int ���v���Ԃ��v��(string �o���w��, string �ړI�w��) 
{
    �w* �o���w = �w::�擾(�o���w��);
    �w* �ړI�w = �w::�擾(�ړI�w��);

    if  (!�s���邩�Ȏ���(*�o���w, *�ړI�w)) {
        return -1;
    }
    if  (�o���w�� == �ړI�w��) {
        return 0;
    }
    int ret = �S��[make_pair(*�o���w, *�ړI�w)];
    if  (ret == 0) {
        ret = �S��[make_pair(*�ړI�w, *�o���w)];
    }
    return ret;
}

// ----------------- ��� ------------------------

#define �s���邩��(�O, ��) �s���邩�Ȏ���(�w(�O), �w(��))

#define �o�����ɍs����(�O, ��) EXPECT_TRUE(�s���邩��(�O, ��) == �s���邩��(��, �O) && �s���邩��(��, �O) == true);
#define �o�����ɍs���Ȃ�(�O, ��) EXPECT_TRUE(�s���邩��(�O, ��) == �s���邩��(��, �O) && �s���邩��(��, �O) == false);

// ----------------- �ۑ�1 ------------------------
// ----------------- �ۑ�3 ------------------------

TEST(IkerukaTest, ��{_���l�͓d�Ԃōs���܂�)
{
    �o�����ɍs����("��{", "���l");
}

TEST(IkerukaTest, �哇_���l�͓d�Ԃł����܂���)
{
    �o�����ɍs���Ȃ�("�哇", "���l");
}

// ----------------- �ۑ�2 ------------------------

TEST(IkerukaTest, ���l_�����͓d�Ԃōs���܂�)
{
    �o�����ɍs����("���l", "����");
}

TEST(IkerukaTest, ����_��{�͓d�Ԃōs���܂�)
{
    �o�����ɍs����("����", "��{");
}

// ----------------- �ۑ�4 ------------------------

TEST(IkerukaTest, �哇�ȊO�̑S�w�݂͌��ɓd�Ԃōs���܂�)
{
    for(int i = 0; i < _countof(�S�w); i++) {
        for(int j = i; j < _countof(�S�w); j++) {
            if (�S�w[i].�w�� == "�哇" || �S�w[j].�w�� == "�哇") {
                �o�����ɍs���Ȃ�(�S�w[i].�w��, �S�w[j].�w��);
            } else {
                �o�����ɍs����(�S�w[i].�w��, �S�w[j].�w��);
            }
        }
    }
}

// ----------------- �ۑ�5 ------------------------

TEST(Ikerukatest, �哇�̗��񂾌o�H�̈ړ����Ԃ��v�Z����) {
    �ړ����Ԃ�ݒ肷��();
    EXPECT_EQ(-1, ���v���Ԃ��v��("�哇", "�V�h"));
}

TEST(Ikerukatest, �����w�̌o�H�̈ړ����Ԃ��v�Z����) {
    EXPECT_EQ(0, ���v���Ԃ��v��("�V�h", "�V�h"));
}

TEST(Ikerukatest, �ׂ荇�����w�Ԃ̈ړ����Ԃ��v�Z����) {
    EXPECT_EQ(32, ���v���Ԃ��v��("��������", "�V�h"));
}
/*
TEST(Ikerukatest, ���p�w�̂���o�H�̈ړ����Ԃ��v�Z����) {
    EXPECT_EQ(73, ���v���Ԃ��v��("��������", "���l"));
}
*/

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}


