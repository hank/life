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
#include <locale>
#include <unordered_map>
#include <sstream>
using std::ifstream;
#include <string>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;
#include <boost/regex.hpp>

#include <boost/tokenizer.hpp>

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

class Kit
{
   public:
      Kit(std::string name)
      : name(name)
      {}
      
      std::string getName() const
      {
         return this->name;
      }

   private:
      std::string name;
};

class BadPartException : public boost::exception, public std::exception
{
   // Intentionally blank
   // Using the standard boost::exception properties
};

class Part
{
   public:
      Part(const std::string& line)
      {
         // Simple validation
         // Line must have characters
         // and first ones need to be numbers
         // Short-circuits to avoid dereferencing line[0] when invalid
         if(line.length() <= 1 ||
               !std::isdigit(line[0])
           )
         {
            BOOST_THROW_EXCEPTION(BadPartException());
         }
         // Use Boost.Tokenizer to parse the line
         boost::tokenizer< boost::escaped_list_separator< char > > tok(line);
         boost::tokenizer< boost::escaped_list_separator< char > >::iterator 
            iter = tok.begin();

         try
         {
            // First field is Quantity
            setQuantity(boost::lexical_cast<int>(*iter++));
         }
         catch(boost::bad_lexical_cast& exception)
         {
            // We've tried to do a bad cast.
            // Simply throw our custom exception
            BOOST_THROW_EXCEPTION(BadPartException());
         }
         // Next is the part number
         setNumber(*iter++);
         // Finally, set the name
         // Trim off any whitespace at the end
         std::string trimmed_name = *iter++;
         boost::trim(trimmed_name);
         setName(trimmed_name);
      }

      std::string getName() const
      {
         return this->name;
      }

      void setName(const std::string& name)
      {
         this->name = name;
      }

      std::string getNumber() const
      {
         return this->number;
      }

      void setNumber(const std::string& number)
      {
         this->number = number;
      }

      int getQuantity() const
      {
         return this->quantity;
      }

      void setQuantity(const uint64_t& quantity)
      {
         this->quantity = quantity;
      }

   private:
      std::string name;
      std::string number;
      int quantity;
};

std::ostream& operator<< (std::ostream &stream, Part& part)
{
   stream << "Part { "
          << part.getQuantity() << ", "
          << part.getNumber() << ", "
          << part.getName() << " }";

   return stream;
}


int main()
{
   // A multimap keyed by part containing Kit and Quantity for each
   std::unordered_multimap<std::string, 
                                std::pair<Kit, uint64_t> > PartMap;

   // Open all csv files in the directory.
   bfs::path current_dir("./BillOfMaterials/");
   boost::regex pattern(".*\\.csv", boost::regex::perl|boost::regex::icase);
   bfs::directory_iterator iter(current_dir);
   bfs::directory_iterator end; // Defaults to past end.
   // For each member
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
            cout << "Processing " << name << "... " << endl;
            // Delete the .csv and copy the Kit name
            std::string kit_name = boost::algorithm::erase_tail_copy(name, 4);
            Kit mykit(kit_name);
            uint32_t parts_processed = 0;
            while(false == myfile.eof())
            {
               std::getline(myfile, line);
               try
               {
                  Part mypart(line);
                  cout << mypart << endl;
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
            myfile.close();
            // Clear our stringstream
            cout << parts_processed << " parts." << endl;
         }
      }
   }

   // Files are processed.  Start the menu system
   while(cin.good())
   {
      // Read a part name
      std::string part_name;
      cout << "Input Part Name: ";
      cin >> part_name;
      if(cin.bad() || cin.eof())
      {
         cout << endl << "Exiting..." << endl;
         break;
      }
      // Find the relevant Part
      
   }
   return EXIT_SUCCESS;
}
