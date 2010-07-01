#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <fstream>
#include <locale>
#include <sstream>
using std::ifstream;
#include <string>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
#include <boost/regex.hpp>

#include "stock.h"
#include "stockutil.h"
#include "stocksnapshot.h"

int main()
{
   // Set up streams and strings for date parsing
   std::stringstream ss;
   // Error checking
   //ss.exceptions(std::ios_base::failbit);
   gregorian::date_input_facet * inputFacet = 
         new gregorian::date_input_facet("%e-%b-%y");
   ss.imbue(std::locale(std::locale::classic(), inputFacet));

   // Open all csv files in the directory.
   path current_dir("./CSVs/");
   boost::regex pattern(".*\\.csv", boost::regex::icase);
   directory_iterator iter(current_dir);
   directory_iterator end;
   for (; iter != end; ++iter)
   {
      std::string name = iter->path().leaf();
      cout << name << endl;
      if (regex_match(name, pattern))
      {
         ifstream myfile(name.c_str(), ifstream::in);
         if(myfile.is_open())
         {
            std::string line;
            cout << "Processing " << name << "..." << endl;
            // Skip the first line by calling getline once.
            std::getline(myfile, line);
            // Create a stock to fill
            Stock mystock;
            uint32_t snapshots_processed = 0;
            while(false == myfile.eof())
            {
               std::getline(myfile, line);
               // Create a stock snapshot by calling with the line
               // and the Date formatting stringstream.
               StockSnapshot snapshot;
               try 
               {
                  snapshot = StockSnapshot(line, ss);
               }
               catch(std::exception& e)
               {
                  // Failed to create StockSnapshot.  Just move on.
                  continue;
               }
               mystock.addSnapshot(snapshot);
               ++snapshots_processed;
            }
            myfile.close();
            // Clear our stringstream
            ss.clear();
            ss.str(std::string());
            if(snapshots_processed > 0)
            {
               cout << "Processed " << snapshots_processed << " snapshots" << endl;
               std::vector<double> macd;
               std::vector<double> emas_9;
               mystock.calculateMACDSeries(emas_9, macd);

               // Calculate 2-day slope
               // Use the number of days to decrement the `end` iterator
               uint32_t num_days = 2;
               double slope = (macd.back() - *(macd.end() - num_days));
               cout << "Slope: " << slope << endl;
            }
         }
      }
   }
   return EXIT_SUCCESS;
}
