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
   cout << "Addition: \n"
        << "\t" << static_cast<std::string>(integer_one) << " + \n"
        << "\t" << static_cast<std::string>(integer_two) << " = \n"
        << "\t" << static_cast<std::string>(integer_three) << endl << endl;
   // Subtraction
   integer_three = integer_two - integer_one;
   cout << "Subtraction: \n"
        << "\t" << static_cast<std::string>(integer_two) << " - \n"
        << "\t" << static_cast<std::string>(integer_one) << " = \n"
        << "\t" << static_cast<std::string>(integer_three) << endl;
   // Multiplication
   integer_one = HugeInt("47239472398472398472333");
   integer_two = HugeInt("3284782397492387498237423");
   integer_three = integer_two * integer_one;
   cout << "Multiplication: \n"
        << "\t" << static_cast<std::string>(integer_two) << " * \n"
        << "\t" << static_cast<std::string>(integer_one) << " = \n"
        << "\t" << static_cast<std::string>(integer_three) << endl;
   // Division
   integer_one = HugeInt("4723947239847239847233373284623874623");
   integer_two = HugeInt("3284782397492387498237423");
   integer_three = integer_one / integer_two;
   cout << "Division: \n"
        << "\t" << static_cast<std::string>(integer_one) << " / \n"
        << "\t" << static_cast<std::string>(integer_two) << " = \n"
        << "\t" << static_cast<std::string>(integer_three) << endl;
   // Division for Kicks...
   integer_one = HugeInt("4723947239847239847233373284623874623");
   integer_two = HugeInt("3");
   integer_three = integer_one / integer_two;
   cout << "Division 2: \n"
        << "\t" << static_cast<std::string>(integer_one) << " / \n"
        << "\t" << static_cast<std::string>(integer_two) << " = \n"
        << "\t" << static_cast<std::string>(integer_three) << endl;

   return EXIT_SUCCESS;
}
