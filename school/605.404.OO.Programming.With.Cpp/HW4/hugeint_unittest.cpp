#include <gtest/gtest.h>
#include <iostream>
#include <string>
using std::string;
#include "hugeint.h"

TEST(HugeInt, StringCast)
{
  HugeInt i(32423432);
  string s = (string)i;
  ASSERT_STREQ("32423432", s.c_str());
  HugeInt j(0);
  s = (string)j;
  ASSERT_STREQ("0", s.c_str());
  HugeInt k("50003000800060004000");
  s = (string)k;
  ASSERT_STREQ("50003000800060004000", s.c_str());
}

TEST(HugeInt, StringAssignmentAndEquality)
{
  HugeInt i = string("7");
  ASSERT_STREQ(((string)i).c_str(), "7");
}

TEST(HugeInt, Negative)
{
  HugeInt i(-1033124);
  string s = (string)i;
  EXPECT_STREQ("1033124", s.c_str());
}

TEST(HugeInt, Zero)
{
  HugeInt i(0);
  string s = (string)i;
  ASSERT_STREQ("0", s.c_str());
}

TEST(HugeInt, IntAssignment)
{
  HugeInt i = 7;
  ASSERT_STREQ(((string)i).c_str(), "7");
}

TEST(HugeInt, HugeIntAssignment)
{
  HugeInt i("12345678912345678900055534200112393811234");
  HugeInt j = i;
  ASSERT_STREQ("12345678912345678900055534200112393811234", ((string)j).c_str());
}

TEST(HugeInt, InitializationOverflow)
{
  HugeInt m("12345678912345678900055534200112393811234000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  HugeInt n("83947238473208947234723984732849023784023000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}

TEST(HugeInt, Addition)
{
  HugeInt i("12345678912345678900055534200112393811234");
  HugeInt j("83947238473208947234723984732849023784023");
  HugeInt l = (i + j);
  ASSERT_STREQ("12345678912345678900055534200112393811234", ((string)i).c_str());
  ASSERT_STREQ("83947238473208947234723984732849023784023", ((string)j).c_str());
  ASSERT_STREQ("96292917385554626134779518932961417595257", ((string)l).c_str());
  HugeInt k = HugeInt(3);
  ASSERT_STREQ("96292917385554626134779518932961417595260", ((string)(i + j + k)).c_str());
  ASSERT_STREQ("96292917385554626134779518932961417595260", ((string)(i + j + 3)).c_str());
}


TEST(HugeInt, Subtraction)
{
  HugeInt j("83947238473208947234723984732849023784023");
  HugeInt i("12345678912345678900055534200112393811234");
  HugeInt l = (j - i);
  ASSERT_STREQ("83947238473208947234723984732849023784023", ((string)j).c_str());
  ASSERT_STREQ("12345678912345678900055534200112393811234", ((string)i).c_str());
  ASSERT_STREQ("71601559560863268334668450532736629972789", ((string)l).c_str());
  // Underflow case
  ASSERT_STREQ("0", ((string)(i - j)).c_str());
}

TEST(HugeInt, Size)
{
  HugeInt i(32423432);
  EXPECT_EQ(8, i.size());
  HugeInt j(0);
  EXPECT_EQ(1, j.size());
}
