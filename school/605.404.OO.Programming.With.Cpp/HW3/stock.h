#ifndef Stock_h
#define Stock_h
#include <vector>
#include <boost/cstdint.hpp>
#include "stockutil.h"
#include "stocksnapshot.h"
class Stock
{
public:
   Stock()
   {
      this->close_vector = NULL;
   }
   
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
