#include <gtest/gtest.h>

struct Station {
    enum enum_t {
        Omiya,
        Yokohama,
        Oshima
    };
};

bool passable(Station::enum_t from, Station::enum_t to)
{
    if (from == Station::Omiya && to == Station::Yokohama)
        return true;

    if (from == Station::Yokohama && to == Station::Oshima)
        return false;

    return false;
}

TEST(PassTest, Positive)
{
    ASSERT_TRUE(passable(Station::Omiya, Station::Yokohama));
    ASSERT_FALSE(passable(Station::Yokohama, Station::Oshima));

    ASSERT_FALSE(passable(Station::Oshima, Station::Omiya));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
