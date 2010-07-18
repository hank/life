// stock.h
// Includes the Stock class
#ifndef Stock_h
#define Stock_h
#include <vector>
#include <boost/cstdint.hpp>
#include "stockutil.h"
#include "stocksnapshot.h"
// Stock Class
// Provides a storage mechanism for a stock with a list of
// StockSnapshots, which store periodic data about the stock.
// Also provides functions to calculate various technical
// analyses on the stock using StockUtil.
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
class Stock
{
public:
   Stock()
      : close_vector(NULL)
   {}
   
   void addSnapshot(StockSnapshot& snapshot)
   {
      this->snapshots.push_back(snapshot);
   }

   const std::vector<StockSnapshot>& getSnapshots() const
   {
      return this->snapshots;
   }

   // Calculate the SMA over a range in our close vector with a given period
   double calculateSMA(std::vector<uint32_t>::const_iterator begin, 
                       std::vector<uint32_t>::const_iterator end) const;

   // Calculate the EMA over a range in our snapshots with a given period
   // Store the series of results in the given vector.
   void calculateEMASeries(std::vector<double>& emas, 
                           uint32_t period);

   // Create and return a vector of close values
   std::vector<uint32_t>* getCloseVector();

   void calculateMACDSeries(std::vector<double>& ema_9, 
                            std::vector<double>& macd);

private:
   // Snapshots in descending order by date
   std::vector<StockSnapshot> snapshots;
   // Close vector storage
   std::vector<uint32_t>* close_vector;
};
#endif // Stock_h
