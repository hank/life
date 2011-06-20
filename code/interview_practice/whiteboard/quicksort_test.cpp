#include <gtest/gtest.h>
#include <stdio.h>
#include "qsort.h"

TEST(Quicksort, Partition)
{
  int a[] = {3,1,2,4,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Call with a pivot selection of index 3 (4)
  int b = partition(a, size, 3);
  // b should now be set to 3
  ASSERT_EQ(3,b);
}

TEST(Quicksort, Partition2)
{
  int a[] = {3,1,2,4,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Call with a pivot selection of index 2 (2)
  int b = partition(a, size, 2);
  // b should now be set to 1
  ASSERT_EQ(1,b);
}

TEST(Quicksort, Partition3)
{
  int a[] = {3,1,2,4,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Call with a pivot selection of index 4 (5)
  int b = partition(a, size, 4);
  // b should now be set to 4
  ASSERT_EQ(4,b);
}

TEST(Quicksort, Sort)
{
  int a[] = {3,1,2,4,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  quicksort(a, size);
  // b should now be set to 4
  for(int i=0; i<size; ++i) {
    ASSERT_EQ(i+1, a[i]);
  }
}

TEST(Quicksort, SortSame)
{
  int a[] = {4,4,4,4,4};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  quicksort(a, size);
  // b should now be set to 4
  for(int i=0; i<size; ++i) {
    ASSERT_EQ(4, a[i]);
  }
}

TEST(Quickselect, Top)
{
  int a[] = {3,4,2,1,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  int t = quickselect(a, size, 1);
  ASSERT_EQ(1,t);
}

TEST(Quickselect, Second)
{
  int a[] = {3,4,2,1,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  int t = quickselect(a, size, 2);
  ASSERT_EQ(2,t);
}

TEST(Quickselect, Third)
{
  int a[] = {3,4,2,1,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  int t = quickselect(a, size, 3);
  ASSERT_EQ(3,t);
}

TEST(Quickselect, Fourth)
{
  int a[] = {3,4,2,1,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  int t = quickselect(a, size, 4);
  ASSERT_EQ(4,t);
}

TEST(Quickselect, Fifth)
{
  int a[] = {3,4,2,1,5};
  int size = sizeof(a) / sizeof(a[0]);
  // Sort the array in place
  int t = quickselect(a, size, 5);
  ASSERT_EQ(5,t);
}
