// stocksnapshot.h
// Contains the StockSnapshot class
#ifndef StockSnapshot_h
#define StockSnapshot_h
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;

// Stock Snapshot
// Keeps a single period of snapshot data for a stock.
// Stores the Open, Close, High, and Low values for a stock as well as a given
// Date.  Purely a data class - almost all functionality is implemented at a
// higher level.
// Stores all currency values in cents.
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
// Date: Thu Jul 1 01:02:12 EDT 2010
class StockSnapshot
{
public:
   // Default Constructor.  Do nothing.
   // Invalid by default
   StockSnapshot()
      : valid(false)
   {}

   // 2-param constructor
   // This initializes the snapshot with a stringstream that outputs a
   // Boost.Date_Time gregorian time.  The stringstream must be initialized
   // and imbued with the proper locales before being sent in.
   // Boost's string library is used to split the string by commas and
   // read the components into the right areas of the class.  The format
   // is as follows:
   // 
   // Date,Open,High,Low,Close,Volume
   // 25-Jun-10,15.13,15.97,14.74,15.57,1560610
   // Volume is ignored for now.
   StockSnapshot(std::string& line, std::stringstream& ss);

   // Print the snapshot to stdout
   void print() const;
   // Get the snapshot's date
   gregorian::date getDate() const;
   // Get the open price
   uint32_t getOpen() const;
   // Get the high price
   uint32_t getHigh() const;
   // Get the low price
   uint32_t getLow() const;
   // Get the close price
   uint32_t getClose() const;
   // Conversion operator for double
   // Returns the close value
   operator double();
   // Returns whether the object is valid
   bool isValid() const 
   {
      return this->valid;
   }

private:
   // Set the date to a given gregorian date
   void setDate(gregorian::date& date);
   // Set the open price
   void setOpen(uint32_t open);
   // Set the high price
   void setHigh(uint32_t high);
   // Set the low price
   void setLow(uint32_t low);
   // Set the close price
   void setClose(uint32_t close);
   // Return the snapshot's close value if cast to double
   gregorian::date date;
   uint32_t open;
   uint32_t high;
   uint32_t low;
   uint32_t close;

   bool valid; // Tells us if we're a valid snapshot
};

// Inlines
inline gregorian::date StockSnapshot::getDate() const
{
   return this->date;
}
inline uint32_t StockSnapshot::getOpen() const
{
   return this->open;
}
inline uint32_t StockSnapshot::getClose() const
{
   return this->close;
}
inline uint32_t StockSnapshot::getHigh() const
{
   return this->high;
}
inline uint32_t StockSnapshot::getLow() const
{
   return this->low;
}
inline void StockSnapshot::setDate(gregorian::date& date)
{
   this->date = date;
}
inline void StockSnapshot::setOpen(uint32_t open)
{
   this->open = open;
}
inline void StockSnapshot::setHigh(uint32_t high)
{
   this->high = high;
}
inline void StockSnapshot::setLow(uint32_t low)
{
   this->low = low;
}
inline void StockSnapshot::setClose(uint32_t close)
{
   this->close = close;
}
// Return the snapshot's close value if cast to double
inline StockSnapshot::operator double()
{
   return this->close;
}
#endif // StockSnapshot_h
