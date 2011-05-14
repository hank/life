#include <cstdio>
#define _USE_MATH_DEFINES
#include <cmath>

struct FooShape
{
  virtual float Area() = 0;
};

struct FooSquare : public FooShape
{
  FooSquare(int lat)
  : lat(lat)
  {}

  virtual float Area()
  {
    return lat * lat;
  }
  private:
  int lat;
};

struct Calculator
{
  Calculator()
  {}
  float get_area(FooShape* fs)
  {
    return fs->Area();
  }
};

struct Shape
{
  virtual float area() = 0;
};

struct Circle : public Shape
{
  Circle(int radius)
  : radius(radius)
  {}

  virtual float area()
  {
    return (M_PI * radius * radius);
  }

  private:
  int radius;
};

struct Rectangle : public Shape
{
  Rectangle(int width, int height)
  : width(width)
  , height(height)
  {}

  virtual float area()
  {
    return width * height;
  }

  private:
  int width;
  int height;
};

struct Square : public Rectangle
{
  Square(int width)
  : Rectangle(width, width)
  {}
};

// Adapter Class for Shape and Calculator
// Object adapter, not a class adapter
struct AdaptedShape : public FooShape
{
  AdaptedShape(Shape* s)
  : _shape(s)
  {}

  // Adapt the Area() call
  virtual float Area()
  {
    return _shape->area();
  }
  private:
  Shape* _shape;
};

int main()
{
  Shape * sp = new Square(5);
  printf("Square area: %f\n", sp->area());
  delete sp;
  sp = new Rectangle(5,10);
  printf("Rectangle area: %f\n", sp->area());
  delete sp;
  sp = new Circle(5);
  printf("Circle area: %f\n", sp->area());

  Calculator c;
  AdaptedShape as(sp);
  printf("Adapted Circle Area: %f\n", 
      c.get_area((FooShape*)&as));

  delete sp;
  return 0;
}
