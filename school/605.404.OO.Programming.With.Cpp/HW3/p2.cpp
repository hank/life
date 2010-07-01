// p2.cpp
// Main program for finding MACD slope
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <utility>
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
namespace bfs = boost::filesystem;
#include <boost/regex.hpp>

#include "stock.h"
#include "stockutil.h"
#include "stocksnapshot.h"

// P2
// Finds the stock in the CSVs directory with the best MACD slope.
// The main function simply opens all the CSV files, turns them into
// StockSnapshot and then Stock objects, then runs algorithms to determine the MACD.
// It then calculates the slope, and finds the most positive one.
//
// Copyright (c) 2010, Erik Gregg
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following
// disclaimer in the documentation and/or other materials provided
// with the distribution.
//
// * Neither the name of Erik Gregg nor the names of his
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Erik Gregg
// Date: Thu Jul 1 01:10:06 EDT 2010
int main()
{
   // Our slopes vector for later fun
   std::vector<std::pair<double, std::string> > slopes;
   // Set up streams and strings for date parsing
   std::stringstream ss;
   // Error checking
   //ss.exceptions(std::ios_base::failbit);
   gregorian::date_input_facet * inputFacet = 
         new gregorian::date_input_facet("%e-%b-%y");
   ss.imbue(std::locale(std::locale::classic(), inputFacet));

   // Open all csv files in the directory.
   bfs::path current_dir("./CSVs/");
   boost::regex pattern(".*\\.csv", boost::regex::perl|boost::regex::icase);
   bfs::directory_iterator iter(current_dir);
   bfs::directory_iterator end; // Defaults to past end.
   for (; iter != end; ++iter)
   {
      std::string name = iter->path().leaf();
      if (regex_match(name, pattern))
      {
         ifstream myfile((iter->path()).string().c_str());
         if(myfile.is_open())
         {
            std::string line;
            cout << "Processing " << name << "... ";
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
               StockSnapshot snapshot(line, ss);
               if(false == snapshot.isValid())
               {
                  // Not a valid snapshot.  Continue.
                  continue;
               }
               // Check to make sure we have a valid date
               mystock.addSnapshot(snapshot);
               ++snapshots_processed;
            }
            myfile.close();
            // Clear our stringstream
            ss.clear();
            ss.str(std::string());
            if(snapshots_processed > 0)
            {
               cout << snapshots_processed << " snapshots." << endl;
               std::vector<double> macd;
               std::vector<double> emas_9;
               mystock.calculateMACDSeries(emas_9, macd);

               // Calculate 2-day slope
               // Use the number of days to decrement the `end` iterator
               uint32_t num_days = 2;
               double slope = macd[0] - macd[num_days - 1];
               // Add slope to our vector.
               std::string stock_name = boost::algorithm::erase_tail_copy(name, 4);
               slopes.push_back(std::pair<double, std::string>(slope, stock_name));
            }
         }
      }
   }
   // Find the best slope
   std::sort(slopes.begin(), slopes.end());
   std::vector<std::pair<double, std::string> >::const_iterator slope_iter =
      slopes.begin();
   while(slope_iter != slopes.end())
   {
      cout << "Slope: " << slope_iter->first << ", " 
                        << slope_iter->second << endl;
      ++slope_iter;
   }
   
   cout << "###" << endl << slopes.back().second << " has the max MACD slope "
      "over the last 2 days." << endl << "###" << endl;
   return EXIT_SUCCESS;
}
