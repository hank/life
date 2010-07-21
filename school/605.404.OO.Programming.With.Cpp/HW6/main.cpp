#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/array.hpp>

#include "passenger.h"
#include "floor.h"

int main()
{
   std::queue<Passenger> passengers;
   boost::array<Elevator, 4> elevators =
   {
      {
         Elevator(), Elevator(), Elevator(), Elevator()
      }
   };
   // Open the file
   std::ifstream myfile("HW6-Elevators.csv");
   std::string line;
   if(myfile.is_open())
   {
      while(!myfile.eof())
      {
         std::getline(myfile, line);
         // Simple validation
         // Line must have characters
         // and first ones need to be numbers
         // Short-circuits to avoid dereferencing line[0] when invalid
         if(line.length() <= 1 ||
            !std::isdigit(line[0])
           )
         {
            continue;
         }
         // Trim the line
         boost::trim(line);
         // Use Boost.Tokenizer to parse the line
         boost::tokenizer< boost::escaped_list_separator< char > > tok(line);
         boost::tokenizer< boost::escaped_list_separator< char > >::iterator
            iter = tok.begin();
         // Set the start time
         uint16_t time = boost::lexical_cast<uint16_t>(*iter++);
         // Next is the starting floor
         uint16_t start_floor = boost::lexical_cast<uint16_t>(*iter++);
         // Finally, set the ending floor
         uint16_t end_floor = boost::lexical_cast<uint16_t>(*iter++);
         // Add it to the list
         Passenger p(time, start_floor, end_floor);
         passengers.push(p);
      }
   }

   // Start ticker
   uint64_t ticker = 0;
   while(ticker < 20000) // Elevators should be done by 20000
   {
      if(passengers.front().getTime() == ticker)
      {
         // A new passenger walks up to the elevators
         cout << passengers.front() << endl;
         passengers.pop();
      }
      ++ticker;
   }
}
