#include <gtest/gtest.h>
#include "factorial.h"

TEST(FactorialTest, Negative) {
  Factorial f(-5);
  EXPECT_EQ(1, (int)f);
  Factorial g(-1);
  EXPECT_EQ(1, (int)g);
}

TEST(FactorialTest, Zero) {
  Factorial f(0);
  EXPECT_EQ(1, (int)f);
}

TEST(FactorialTest, Positive) {
  Factorial f(1);
  EXPECT_EQ(1, (int)f);
  Factorial g(2);
  EXPECT_EQ(2, (int)g);
  Factorial h(3);
  EXPECT_EQ(6, (int)h);
  Factorial i(8);
  EXPECT_EQ(40320, (int)i);
}
