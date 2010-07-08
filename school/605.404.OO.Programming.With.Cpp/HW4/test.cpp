// test.cpp
// Test program
#include <iostream>
using std::cout;
using std::endl;
#include "hugeint.h"

int main()
{
   HugeInt integer_one("2389472398472394723047239472398472398472333");
   HugeInt integer_two("8374928307412364712367891263781236218963721");
   HugeInt integer_three = integer_one + integer_two;
   // Addition
   cout << "Addition: ";
   if(integer_three == HugeInt("10764400705884759435415130736179708617436054"))
   {
      cout << "Success!" << endl;
   }
   else
   {
      cout << "Failure: " << static_cast<std::string>(integer_three) << endl;
   }
   // Subtraction
   integer_three = integer_two - integer_one;
   cout << "Subtraction: ";
   if(integer_three == HugeInt("5985455908939969989320651791382763820491388"))
   {
      cout << "Success!" << endl;
   }
   else
   {
      cout << "Failure: " << static_cast<std::string>(integer_three) << endl;
   }
   // Multiplication
   integer_one = HugeInt("47239472398472398472333");
   integer_two = HugeInt("3284782397492387498237423");
   integer_three = integer_two * integer_one;
   cout << "Multiplication: ";
   if(integer_three == HugeInt("155171387401329629824628750483314580355330717859"))
   {
      cout << "Success!" << endl;
   }
   else
   {
      cout << "Failure: " << static_cast<std::string>(integer_three) << endl;
   }
   // Division
   integer_one = HugeInt("4723947239847239847233373284623874623");
   integer_two = HugeInt("3284782397492387498237423");
   integer_three = integer_one / integer_two;
   cout << "Division: ";
   if(integer_three == HugeInt("1438130953043"))
   {
      cout << "Success!" << endl;
   }
   else
   {
      cout << "Failure: " << static_cast<std::string>(integer_three) << endl;
   }
   // Division for Kicks...
   integer_one = HugeInt("4723947239847239847233373284623874623");
   integer_two = HugeInt("3");
   integer_three = integer_one / integer_two;
   cout << "Division 2: ";
   if(integer_three == HugeInt("1574649079949079949077791094874624874"))
   {
      cout << "Success!" << endl;
   }
   else
   {
      cout << "Failure: " << static_cast<std::string>(integer_three) << endl;
   }

   return EXIT_SUCCESS;
}
