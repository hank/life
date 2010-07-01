// stockutil.h
// Contains the StockUtil class
#ifndef StockUtil_h
#define StockUtil_h
#include <vector>
// StockUtil Class
// Singleton class the provides utility algorithms for technical
// stock analysis.  Analyzes arbitrary series stored in vectors.
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
// Singleton
class StockUtil
{
public:
   // cannot use 'this' in a static function
   static const StockUtil* getInstance()
   {
      if(!instance)
      {
         instance = new StockUtil;
      }
      return instance;
   }

   // Calculate the SMA over a range in a source vector slice
   // Period is the distance between the two
   // Vector type must be promotable to double for addition to numerator
   template <class T>
   double calculateSMA(typename std::vector<T>::const_iterator begin, 
                       typename std::vector<T>::const_iterator end) const;

   // Calculate the EMA of the series of values given in source,
   // Use the given period, store the result in emas.
   // Vector type must be promotable to double for calculation
   template <class T>
   void calculateEMASeries(std::vector<double>& emas, 
                           const std::vector<T>& source, 
                           unsigned int period) const;

   // Calculate the MACD and 9-day EMA given some source data.
   // Use the given period, store the result in macd and ema_9.
   // Vector type must be promotable to double for calculation
   template <class T>
   void calculateMACDSeries(std::vector<double>& emas_9, 
                            std::vector<double>& macd, 
                            const std::vector<T>& source) const;

private:
   // Private ctor, dtor, and copy
   StockUtil(){}
   StockUtil(StockUtil& rhs){}
   // Make sure to delete the only instance of the class.
   ~StockUtil()
   {
      delete this->instance;
   }
   static StockUtil* instance;
};

// Templated functions.  Must be in the header.

// Builds up a numerator and divides by the period.
template <class T>
double StockUtil::calculateSMA(typename std::vector<T>::const_iterator begin, 
                               typename std::vector<T>::const_iterator end) 
                                                                        const
{
   double sma_numerator = 0.0;
   double sma = 0.0;
   int period = end - begin;
   // Return SMA = 0 if the following is false
   if(period > 0)
   {
      // Build up the initial numerator
      while(begin < end)
      {
         sma_numerator += *begin;
         ++begin;
      }
      if(sma_numerator != 0.0) 
      {
         sma = sma_numerator / period;
      }
   }
   return sma;
}

// Find the SMA, then use it as the initial value for the EMA.
// EMA is calculated using the standard EMA formula found here:
// http://bit.ly/w3dUP
template <class T>
void StockUtil::calculateEMASeries(std::vector<double>& emas, 
                                   const std::vector<T>& source, 
                                   unsigned int period) const
{
   // Begin by finding the SMA and using it as the initial EMA value
   // Set to begin before the EMA period
   typename std::vector<T>::const_iterator iter = source.end() - period;
   // PDA = Prior Day Average
   double pda = calculateSMA<T>(iter, source.end());
   // If we get 0 back, we've failed to calculate a proper SMA
   if(pda > 0.0)
   {
      // Reset iter to first value for EMA calculation
      // Set to begin before the EMA period
      iter = source.end() - period - 1; 
      double exponent = 2.0 / (period + 1);
      // Now, use the SMA as the initial value and iteratively calculate EMA
      while(iter != source.begin())
      {
         // CDV = Current Day's Value
         double cdv = *iter;
         // (CDV * Exp) + (PDA * (1 - Exp)) = EMA 
         double ema = (cdv * exponent) + (pda * (1.0 - exponent));
         emas.push_back(ema);
         // Set Prior Day Average to current EMA
         pda = ema;
         // Move our iterator
         --iter;
      }
   }
}

// Finds the EMA for various periods, then takes the vector difference
// and returns the 9-period EMA along with the MACD for 12 ans 26 days.
template <class T>
void StockUtil::calculateMACDSeries(std::vector<double>& emas_9, 
                                    std::vector<double>& macd, 
                                    const std::vector<T>& source) const
{
   // Find our 12-period EMA
   std::vector<double> emas_12;
   calculateEMASeries<T>(emas_12, source, 12);
   // Find our 26-period EMA
   std::vector<double> emas_26;
   calculateEMASeries<T>(emas_26, source, 26);
   // MACD is 12-period minus the 26-period
   std::vector<double>::const_iterator iter_12 = emas_12.begin();
   std::vector<double>::const_iterator iter_26 = emas_26.begin();
   while(iter_12 != emas_12.end() &&
         iter_26 != emas_26.end()
        )
   {
      macd.push_back(*iter_12 - *iter_26);
      ++iter_12;
      ++iter_26;
   }
   // Find our 9-period EMA on MACD
   calculateEMASeries<double>(emas_9, macd, 9);
}
#endif // StockUtil_h
