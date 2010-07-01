#ifndef StockUtil_h
#define StockUtil_h
#include <vector>
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
