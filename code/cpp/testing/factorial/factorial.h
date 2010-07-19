/* Simple factorial generation class.  Takes one parameter and
 * generates the corresponding number in the factorial series.
 */
class Factorial {
  int result;

  public:
  Factorial(int i)
  {
    if(i < 1) result = 1;
    else {
      result = i--;
      while(i > 0) {
        result *= i;
        i--;
      }
    }
  };
  operator int() { return result; }
};
