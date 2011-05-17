// Defines an abstract class that concrete classes inherit from.  The users of
// the abstract class don't have to commit to use of a single concrete
// implementation.  We make things using an abstract factory class pointer.
#include <cstdio>
struct AbstractFactory
{
  AbstractFactory(int foo, int bar)
  : foo(foo)
  , bar(bar)
  {}
  virtual int make_foo() = 0;
  virtual int make_bar() = 0;
  protected:
  int foo;
  int bar;
};

struct ManateeFactory : public AbstractFactory
{
  ManateeFactory()
  : AbstractFactory(1,2)
  {}

  virtual int make_foo()
  {
    return this->foo;
  }

  virtual int make_bar()
  {
    return this->bar;
  }
};

struct DugongFactory : AbstractFactory
{
  DugongFactory()
  : AbstractFactory(3,4)
  {}

  virtual int make_foo()
  {
    return this->foo*2;
  }

  virtual int make_bar()
  {
    return this->bar*2;
  }
};

struct UserClass
{
  static void go(AbstractFactory& af)
  {
    int foo = af.make_foo();
    int bar = af.make_bar();
    printf("Foo: %d\n", foo);
    printf("Bar: %d\n", bar);
  }
};

int main()
{
  ManateeFactory mf;
  DugongFactory df;
  // Test our Manatee Factory
  UserClass::go(mf);
  // Test our Dugong Factory
  UserClass::go(df);
  return 0;
}
