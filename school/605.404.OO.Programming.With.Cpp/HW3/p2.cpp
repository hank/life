#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <fstream>
#include <locale>
#include <sstream>
using std::ifstream;
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#include <boost/algorithm/string.hpp>

// Store all currency values in cents
class StockSnapshot
{
public:
   gregorian::date Date;
   uint64_t open;
   uint64_t high;
   uint64_t low;
   uint64_t close;
};

class Stock
{
public:
   std::vector<StockSnapshot> snapshots;
};

int main()
{
   // Set up streams and strings for date parsing
   std::string line;
   std::stringstream ss;
   ss.exceptions(std::ios_base::failbit);
   gregorian::date_input_facet * inputFacet = new gregorian::date_input_facet("%e-%b-%y");
   ss.imbue(std::locale(std::locale::classic(), inputFacet));

   ifstream myfile("BZ.csv");
   if(myfile.is_open())
   {
      // Skip the first line by calling getline once.
      std::getline(myfile, line);
      // Create a stock to fill
      Stock mystock;
      while(false == myfile.eof())
      {
         std::vector<std::string> inStrings;
         std::getline(myfile, line);
         boost::algorithm::split(inStrings, line, boost::is_any_of(","));
         gregorian::date test;
         // Check to see if we have a single-digit day-of-the-month
         // If so, just stream a leading
         if(inStrings[0][1] == '-') ss << "0";
         ss << inStrings[0];
         ss >> test;
         // This breaks when parsing single-digit days of the month..
         cout << inStrings[0] << " : " << test << endl;
         // Create a stock snapshot
         
         
      }
      myfile.close();
   }
   return EXIT_SUCCESS;
}
