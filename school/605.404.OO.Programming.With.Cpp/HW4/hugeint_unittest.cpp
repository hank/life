#include <gtest/gtest.h>
#include <iostream>
#include <string>
using std::string;
#include "hugeint.h"

TEST(HugeInt, IntCast)
{
  HugeInt i(1032423124);
  EXPECT_EQ(1032423124, (int)i);
}

TEST(HugeInt, Negative)
{
  ASSERT_ANY_THROW(HugeInt i(-1033124));
}

TEST(HugeInt, Zero)
{
  HugeInt i(0);
  ASSERT_EQ(0, (int)i);
}

TEST(HugeInt, Size)
{
  HugeInt i(32423432);
  ASSERT_EQ(8, i.size());
  //HugeInt j(0);
  //ASSERT_STREQ("0", (char *)i);
}

TEST(HugeInt, StringCast)
{
  HugeInt i(32423432);
  string s = (string)i;
  ASSERT_STREQ("32423432", s.c_str());
  //HugeInt j(0);
  //ASSERT_STREQ("0", (char *)i);
}
