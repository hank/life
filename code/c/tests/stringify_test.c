#include <stdio.h>
#define CONFIG_FOO 1
#define CONFIG_NOO 0

#define is_set(macro) is_set_(macro)
#define macrotest_1 ,
#define is_set_(value) is_set__(macrotest_##value)
#define is_set__(comma) is_set___(comma 1, 0)
#define is_set___(_, v, ...) v

int main()
{
  printf("It's %d!\n", is_set(FOO));
  if(is_set(CONFIG_FOO))
  {
    puts("And it's true, yo!");
  }
  if(is_set(CONFIG_NOO))
  {
    puts("Noooo!");
  }
  if(is_set(CONFIG_NOTEXIST))
  {
    puts("NOT EXIST");
  }
  return 0;
}
