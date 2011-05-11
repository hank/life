// Defines an abstract class that concrete classes inherit from.  The users of
// the abstract class don't have to commit to use of a single concrete
// implementation.  Instead, they make use of polymorphism through the
// abstract member functions of the parent factory class to access the child
// factory classes transparently.
#include <cstdio>
struct AbstractFactory
{
  AbstractFactory(int foo, int bar)
  : foo(foo)
  , bar(bar)
  {}
  virtual int get_foo() = 0;
  virtual int get_bar() = 0;
  protected:
  int foo;
  int bar;
};

struct ManateeFactory : public AbstractFactory
{
  ManateeFactory()
  : AbstractFactory(1,2)
  {}

  virtual int get_foo()
  {
    return this->foo;
  }

  virtual int get_bar()
  {
    return this->bar;
  }
};

struct DugongFactory : AbstractFactory
{
  DugongFactory()
  : AbstractFactory(3,4)
  {}

  virtual int get_foo()
  {
    return this->foo*2;
  }

  virtual int get_bar()
  {
    return this->bar*2;
  }
};

struct UserClass
{
  static void go(AbstractFactory& af)
  {
    printf("Foo: %d\n", af.get_foo());
    printf("Bar: %d\n", af.get_bar());
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
