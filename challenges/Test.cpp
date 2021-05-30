#include <gtest/gtest.h>

namespace
{
TEST(HelloWorld, first)
{
    EXPECT_STREQ("Love", "Love");
    EXPECT_EQ(56, 56);
}
}
