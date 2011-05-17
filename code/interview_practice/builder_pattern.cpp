// We have a converter base class that has different conversion
// implementations as children.  One is uppercase and one is lowercase.  Our
// reader class calls these using the parent class's abstract functions.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

struct Builder
{
  virtual char convert(char c) const = 0;
};

struct UCBuilder : public Builder
{
  virtual char convert(char c) const 
  {
    return toupper(c);
  }
};

struct LCBuilder : public Builder
{
  virtual char convert(char c) const 
  {
    return tolower(c);
  }
};

struct TextConverter
{
  static void go(char * text, Builder& b)
  {
    if(!text) return;
    while(char c = *text)
    {
      *text = b.convert(c);
      ++text;
    }
  }
};

int main()
{
  UCBuilder uc;
  LCBuilder lc;
  char c[11] = {0};
  memcpy(c, "Manatees!", 9);
  TextConverter::go(c, lc);
  printf("LC: %s\n", c);
  TextConverter::go(c, uc);
  printf("UC: %s\n", c);
}
