#include <iostream>
using namespace std;
struct Currency
{
  Currency(int whole, int decimal)
  : whole(whole)
  , decimal(decimal)
  {}

  virtual void print(ostream& os) const
  {
    os << whole << "." << decimal;
  }

  Currency operator+(const Currency& other) const
  {
    Currency c(*this);
    c.whole += other.whole;
    c.decimal += other.decimal;
    // Account for overflow
    while(c.decimal > 100)
    {
      c.whole += 1;
      c.decimal -= 100;
    }
    return c;
  }

  Currency operator-(const Currency& other) const
  {
    Currency c(*this);
    c.whole -= other.whole;
    c.decimal -= other.decimal;
    // Account for underflow
    while(c.decimal < 0)
    {
      c.whole -= 1;
      c.decimal += 100;
    }
    return c;
  }

  Currency operator*(int factor) const
  {
    Currency c(*this);
    c.whole *= factor;
    c.decimal *= factor;
    c.whole += c.decimal / 100;
    c.decimal %= 100;
    return c;
  }

  protected:
  int whole;
  int decimal;
};

struct Euro : public Currency
{
  Euro(int whole, int decimal)
  : Currency(whole, decimal)
  {}

  virtual void print(ostream& os) const
  {
    os << "Yeeeeero: " << whole << "." << decimal;
  }
};

ostream& operator<<(ostream& os, Currency& c)
{
  c.print(os);
  return os;
}

int main()
{
  Currency c(5, 50);
  Currency d(3, 75);
  Currency p = c - d;
  cout << p << endl;
  p = c * 3;
  cout << p << endl;
  p = c + d;
  cout << p << endl;

  // Oh yeah yeah, polymorphism!
  Euro e(11, 70);
  Currency* l = &e;
  cout << *l << endl;

  return 0;
}
