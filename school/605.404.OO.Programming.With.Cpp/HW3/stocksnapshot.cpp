// stocksnapshot.cpp
// Contains the StockSnapshot implementation
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <sstream>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#include <boost/algorithm/string.hpp>

#include "stocksnapshot.h"

// Sets valid to true, and sets to false if anything bad happens.
StockSnapshot::StockSnapshot(std::string& line, std::stringstream& ss)
  : valid(true)
{
   gregorian::date date;
   std::vector<std::string> inStrings;
   boost::algorithm::split(inStrings, line, boost::is_any_of(","));
   // Check to see if we have a single-digit day-of-the-month
   if(inStrings[0][1] == '-')
   {
      // If so, just stream a leading 0
      ss << "0";
   }
   // Input date from file into stringstream
   ss << inStrings[0];
   // Output it into new date object
   ss >> date;
   // Set our date with the date object
   setDate(date);
   if(getDate().is_not_a_date())
   {
      // Skip this one and move on.
      this->valid = false;
   }
   // Create a stock snapshot
   // Immediately converts to cents as to avoid later arithmetic errors.
   // Double precision is good enough to hold 2-digit decimal.
   try 
   {
      setOpen (100 * boost::lexical_cast<double>(inStrings[1]));
      setHigh (100 * boost::lexical_cast<double>(inStrings[2]));
      setLow  (100 * boost::lexical_cast<double>(inStrings[3]));
      setClose(100 * boost::lexical_cast<double>(inStrings[4]));
   }
   catch(boost::bad_lexical_cast& e)
   {
      // Set object validity to false
      this->valid = false;
   }
}

// Print to stdout
void StockSnapshot::print() const
{
   cout << "Snapshot {"
      << this->date << ", "
      << this->open << ", "
      << this->high << ", "
      << this->low << ", "
      << this->close << "}" << endl;
}

