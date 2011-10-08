#include <gtest/gtest.h>
#include <string>
#include <map>

using std::string;
using std::pair;
using std::map;
using std::make_pair;

struct ‰w {
    const string ‰w–¼;

    ‰w(string ‰w–¼) : ‰w–¼(‰w–¼) {}
    static ‰w* æ“¾(string ‰w–¼);

    bool operator<(const ‰w& ‰w) const {
        return ‰w.‰w–¼ < ‰w–¼;
    }
};

‰w ‘S‰w[] = {
    ‰w("‘å“‡"),
    ‰w("‰¡•l"),
    ‰w("‘å‹{"),
    ‰w("“Œ‹"),
    ‰w("“ì‰Y˜a"),
    ‰w("Ô‰H"),
    ‰w("’r‘Ü"),
    ‰w("“c’["),
    ‰w("¼‘•ª›"),
    ‰w("Vh"),
    ‰w("Œä’ƒƒm…"),
    ‰w("H—tŒ´"),
    ‰w("a’J"),
    ‰w("•‘ ¬™"),
    ‰w("ìè"),
};

‰w* ‰w::æ“¾(string ‰w–¼) {
    for (int i = 0; i < _countof(‘S‰w); i++) {
        if (‘S‰w[i].‰w–¼ == ‰w–¼) {
            return &‘S‰w[i];
        }
    }
    return NULL;
}


map<pair<‰w, ‰w>, int> ‘Sü;

void ˆÚ“®ŠÔ‚ğİ’è‚·‚é() {
    ‘Sü[make_pair(*‰w::æ“¾("Vh"), *‰w::æ“¾("¼‘•ª›"))] = 32;
/*
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    ‘Sü[make_pair(‰w::æ“¾("Vh"), ‰w::æ“¾("Vh"))] = 0;
    */
    }

bool s‚¯‚é‚©‚ÈÀ‘•(‰w o”­‰w, ‰w –Ú“I‰w) 
{
    if (o”­‰w.‰w–¼ == "‘å“‡" || –Ú“I‰w.‰w–¼ == "‘å“‡") {
        return false;
    }
    return true;
}

int Š—vŠÔ‚ğŒv‚é(string o”­‰w–¼, string –Ú“I‰w–¼) 
{
    ‰w* o”­‰w = ‰w::æ“¾(o”­‰w–¼);
    ‰w* –Ú“I‰w = ‰w::æ“¾(–Ú“I‰w–¼);

    if  (!s‚¯‚é‚©‚ÈÀ‘•(*o”­‰w, *–Ú“I‰w)) {
        return -1;
    }
    if  (o”­‰w–¼ == –Ú“I‰w–¼) {
        return 0;
    }
    int ret = ‘Sü[make_pair(*o”­‰w, *–Ú“I‰w)];
    if  (ret == 0) {
        ret = ‘Sü[make_pair(*–Ú“I‰w, *o”­‰w)];
    }
    return ret;
}

// ----------------- •â‘è ------------------------

#define s‚¯‚é‚©‚È(‘O, Œã) s‚¯‚é‚©‚ÈÀ‘•(‰w(‘O), ‰w(Œã))

#define ‘o•ûŒü‚És‚¯‚é(‘O, Œã) EXPECT_TRUE(s‚¯‚é‚©‚È(‘O, Œã) == s‚¯‚é‚©‚È(Œã, ‘O) && s‚¯‚é‚©‚È(Œã, ‘O) == true);
#define ‘o•ûŒü‚És‚¯‚È‚¢(‘O, Œã) EXPECT_TRUE(s‚¯‚é‚©‚È(‘O, Œã) == s‚¯‚é‚©‚È(Œã, ‘O) && s‚¯‚é‚©‚È(Œã, ‘O) == false);

// ----------------- ‰Û‘è1 ------------------------
// ----------------- ‰Û‘è3 ------------------------

TEST(IkerukaTest, ‘å‹{_‰¡•l‚Í“dÔ‚Ås‚¯‚Ü‚·)
{
    ‘o•ûŒü‚És‚¯‚é("‘å‹{", "‰¡•l");
}

TEST(IkerukaTest, ‘å“‡_‰¡•l‚Í“dÔ‚Å‚¢‚¯‚Ü‚¹‚ñ)
{
    ‘o•ûŒü‚És‚¯‚È‚¢("‘å“‡", "‰¡•l");
}

// ----------------- ‰Û‘è2 ------------------------

TEST(IkerukaTest, ‰¡•l_“Œ‹‚Í“dÔ‚Ås‚¯‚Ü‚·)
{
    ‘o•ûŒü‚És‚¯‚é("‰¡•l", "“Œ‹");
}

TEST(IkerukaTest, “Œ‹_‘å‹{‚Í“dÔ‚Ås‚¯‚Ü‚·)
{
    ‘o•ûŒü‚És‚¯‚é("“Œ‹", "‘å‹{");
}

// ----------------- ‰Û‘è4 ------------------------

TEST(IkerukaTest, ‘å“‡ˆÈŠO‚Ì‘S‰w‚ÍŒİ‚¢‚É“dÔ‚Ås‚¯‚Ü‚·)
{
    for(int i = 0; i < _countof(‘S‰w); i++) {
        for(int j = i; j < _countof(‘S‰w); j++) {
            if (‘S‰w[i].‰w–¼ == "‘å“‡" || ‘S‰w[j].‰w–¼ == "‘å“‡") {
                ‘o•ûŒü‚És‚¯‚È‚¢(‘S‰w[i].‰w–¼, ‘S‰w[j].‰w–¼);
            } else {
                ‘o•ûŒü‚És‚¯‚é(‘S‰w[i].‰w–¼, ‘S‰w[j].‰w–¼);
            }
        }
    }
}

// ----------------- ‰Û‘è5 ------------------------

TEST(Ikerukatest, ‘å“‡‚Ì—‚ñ‚¾Œo˜H‚ÌˆÚ“®ŠÔ‚ğŒvZ‚·‚é) {
    ˆÚ“®ŠÔ‚ğİ’è‚·‚é();
    EXPECT_EQ(-1, Š—vŠÔ‚ğŒv‚é("‘å“‡", "Vh"));
}

TEST(Ikerukatest, “¯‚¶‰w‚ÌŒo˜H‚ÌˆÚ“®ŠÔ‚ğŒvZ‚·‚é) {
    EXPECT_EQ(0, Š—vŠÔ‚ğŒv‚é("Vh", "Vh"));
}

TEST(Ikerukatest, —×‚è‡‚Á‚½‰wŠÔ‚ÌˆÚ“®ŠÔ‚ğŒvZ‚·‚é) {
    EXPECT_EQ(32, Š—vŠÔ‚ğŒv‚é("¼‘•ª›", "Vh"));
}
/*
TEST(Ikerukatest, ’†Œp‰w‚Ì‚ ‚éŒo˜H‚ÌˆÚ“®ŠÔ‚ğŒvZ‚·‚é) {
    EXPECT_EQ(73, Š—vŠÔ‚ğŒv‚é("¼‘•ª›", "‰¡•l"));
}
*/

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	return ret;
}


