struct Vehicle
{
  virtual void start() = 0;
};

struct Car : Vehicle
{
  Car()
  : Vehicle()
  , started(false)
  {}

  virtual void start()
  {
    this->started = true;
  }

  private:
  bool started;
};

int main()
{
  Car c;
  c.start();
  return 0;
}


