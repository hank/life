// bill_of_materials.cpp
// Main program for processing a bill of materials
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
#include <iterator>
#include <utility>
#include <fstream>
#include <unordered_map>
using std::ifstream;
#include <string>
#include <boost/cstdint.hpp>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;
#include <boost/regex.hpp>

#include "kit.h"
#include "part.h"

// Bill of Materials
// Processes all the files in the BillOfMaterials Directory
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
   // A multimap keyed by part containing Kit and Quantity for each
   typedef boost::unordered_multimap<Part, 
                                   std::pair<Kit, uint64_t> > umulmap_type;
   umulmap_type PartMap;

   // Open all csv files in the directory.
   bfs::path current_dir("./BillOfMaterials/");
   boost::regex pattern(".*\\.csv", boost::regex::perl|boost::regex::icase);
   bfs::directory_iterator iter(current_dir);
   bfs::directory_iterator end; // Defaults to past end.
   // For each member
   uint32_t parts_processed = 0;
   uint32_t kits_processed = 0;
   for (; iter != end; ++iter)
   {
      // Get filename
      std::string name = iter->path().leaf();
      // If it matches our regex
      if (regex_match(name, pattern))
      {
         // Open the file
         ifstream myfile((iter->path()).string().c_str());
         if(myfile.is_open())
         {
            std::string line;
            //cout << "Processing " << name << "... " << endl;
            // Delete the .csv and copy the Kit name
            std::string kit_name = boost::algorithm::erase_tail_copy(name, 4);
            Kit mykit(kit_name);
            while(false == myfile.eof())
            {
               std::getline(myfile, line);
               try
               {
                  Part mypart(line);
                  //cout << mypart << endl;
                  // Try to add Part to multimap

                  umulmap_type::mapped_type mypair(mykit, 
                                                   mypart.getQuantity());
                  PartMap.insert(umulmap_type::value_type(mypart,
                                                          mypair));
               }
               catch(const BadPartException& exception)
               {
                  // Just a simple bad part exception
                  // Parsing the line must have failed
                  // Just continue on
                  //cout << boost::diagnostic_information(exception) << endl;
                  continue;
               }
               ++parts_processed;
            }
            ++kits_processed;
            myfile.close();
         }
      }
   }
   cout << "Processed " << kits_processed << " kits; "
        << parts_processed << " parts" << endl;

   // Files are processed.  Start the menu system
   while(cin.good())
   {
      // Read a part name
      std::string part_number;
      cout << "Input Part Number: ";
      std::getline(cin, part_number);
      if(cin.bad() || cin.eof())
      {
         cout << endl << "Exiting..." << endl;
         break;
      }
      // Find the relevant Part
      // First, trim whitespace from the string
      boost::trim(part_number);
      // Make a dummy part for searching
      Part search_part;
      search_part.setNumber(part_number);

      // Create a pair of iterators for the kits
      // and call equal_range on our part to assign
      std::pair<umulmap_type::const_iterator, 
                umulmap_type::const_iterator> iter_pair = 
                     PartMap.equal_range(search_part);

      if(iter_pair.first != iter_pair.second)
      {
         cout << "Found!" << endl;
         // Output Part Information
         cout << iter_pair.first->first << endl;
         while(iter_pair.first != iter_pair.second)
         {
            // A bit tricky.  A pair of iterators, pointing to a
            // key/value pair, with a value of a pair!
            cout << "\tKit: " << iter_pair.first->second.first
                 << ", Quantity: " << iter_pair.first->second.second << endl;
            ++iter_pair.first;
         }
      }
      else
      {
         cout << "Not Found..." << endl;
      }
   }
   return EXIT_SUCCESS;
}
