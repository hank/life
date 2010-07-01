#include "stockutil.h"
#include "stock.h"

// Simply map our close values onto a new vector and use the
// StockUtil function to calculate
double Stock::calculateSMA(std::vector<uint32_t>::const_iterator begin, 
                           std::vector<uint32_t>::const_iterator end) const
{
   const StockUtil * stock_util = StockUtil::getInstance();
   // Return result of SMA
   return stock_util->calculateSMA<uint32_t>(begin, end);
}

// Simply map our close values onto a new vector and use the
// StockUtil function to calculate
void Stock::calculateEMASeries(std::vector<double>& emas, 
                               unsigned int period)
{
   const StockUtil * stock_util = StockUtil::getInstance();
   // Pass by referencoe
   std::vector<uint32_t>* close_vector = getCloseVector();
   stock_util->calculateEMASeries<uint32_t>(emas, *close_vector, period);
}

// Simply map our close values onto a new vector and use the
// StockUtil function to calculate
void Stock::calculateMACDSeries(std::vector<double>& ema_9, 
                                std::vector<double>& macd)
{
   const StockUtil * stock_util = StockUtil::getInstance();
   // Pass by referencoe
   std::vector<uint32_t>* close_vector = getCloseVector();
   stock_util->calculateMACDSeries<uint32_t>(ema_9, macd, *close_vector);
}

// Creates the vector if necessary and stores it in the class.
std::vector<uint32_t>* Stock::getCloseVector()
{
   if(!this->close_vector)
   {
      this->close_vector = new std::vector<unsigned int>;
      // Build it and return it
      std::vector<StockSnapshot>::const_iterator snap_iter = 
         this->snapshots.end();
      while(snap_iter != this->snapshots.begin())
      {
         this->close_vector->push_back(snap_iter->getClose());
         --snap_iter;
      }
   }
   return this->close_vector;
}
