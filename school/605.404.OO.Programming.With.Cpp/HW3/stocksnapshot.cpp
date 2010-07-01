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

StockSnapshot::StockSnapshot(std::string& line, std::stringstream& ss)
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
   // Check to make sure we have a valid date
   if(date.is_not_a_date())
   {
      // Throw generic exception.
      throw;
   }
   // Set our date with the date object
   setDate(date);
   // Create a stock snapshot
   // Immediately converts to cents as to avoid later arithmetic errors.
   // Double precision is good enough to hold 2-digit decimal.
   setOpen (100 * boost::lexical_cast<double>(inStrings[1]));
   setHigh (100 * boost::lexical_cast<double>(inStrings[2]));
   setLow  (100 * boost::lexical_cast<double>(inStrings[3]));
   setClose(100 * boost::lexical_cast<double>(inStrings[4]));
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

