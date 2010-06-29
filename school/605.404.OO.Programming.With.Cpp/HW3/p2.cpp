#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <fstream>
#include <locale>
#include <sstream>
using std::ifstream;
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;
#include <boost/algorithm/string.hpp>

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
   double calculateSMA(std::vector<double>::const_iterator begin, 
                       std::vector<double>::const_iterator end) const
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

   // Calculate the EMA of the series of values given in source,
   // Use the given period, store the result in emas.
   void calculateEMASeries(std::vector<double>& emas, 
                           const std::vector<double>& source, 
                           unsigned int period) const
   {
      // Begin by finding the SMA and using it as the initial EMA value
      // Set to begin before the EMA period
      std::vector<double>::const_iterator iter = source.end() - period;
      // PDA = Prior Day Average
      double pda = calculateSMA(iter, source.end());
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
   
private:
   StockUtil(){}
   ~StockUtil()
   {
      delete this->instance;
   }
   static StockUtil* instance;
};

StockUtil* StockUtil::instance = 0;

// Store all currency values in cents
class StockSnapshot
{
public:
   gregorian::date getDate() const
   {
      return this->date;
   }
   double getOpen() const
   {
      return this->open;
   }
   double getClose() const
   {
      return this->close;
   }
   double getHigh() const
   {
      return this->high;
   }
   double getLow() const
   {
      return this->low;
   }
   void setDate(gregorian::date& date)
   {
      this->date = date;
   }
   void setOpen(double open)
   {
      this->open = open;
   }
   void setHigh(double high)
   {
      this->high = high;
   }
   void setLow(double low)
   {
      this->low = low;
   }
   void setClose(double close)
   {
      this->close = close;
   }
   void print() const
   {
      cout << "Snapshot {"
           << this->date << ", "
           << this->open << ", "
           << this->high << ", "
           << this->low << ", "
           << this->close << "}" << endl;
   }
private:
   gregorian::date date;
   double open;
   double high;
   double low;
   double close;
};

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
   double calculateSMA(std::vector<double>::const_iterator begin, 
                       std::vector<double>::const_iterator end) const
   {
      // Simply map our close values onto a new vector and use the
      // StockUtil function to calculate
      const StockUtil * stock_util = StockUtil::getInstance();
      // Return result of SMA
      return stock_util->calculateSMA(begin, end);
   }

   // Calculate the EMA over a range in our snapshots with a given period
   // Store the series of results in the given vector.
   void calculateEMASeries(std::vector<double>& emas, 
                           unsigned int period)
   {
      // Simply map our close values onto a new vector and use the
      // StockUtil function to calculate
      const StockUtil * stock_util = StockUtil::getInstance();
      // Pass by referencoe
      std::vector<double>* close_vector = getCloseVector();
      stock_util->calculateEMASeries(emas, *close_vector, period);
   }

   // Create and return a vector of close values
   std::vector<double>* getCloseVector()
   {
      if(!this->close_vector)
      {
         this->close_vector = new std::vector<double>;
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
private:
   // Snapshots in descending order by date
   std::vector<StockSnapshot> snapshots;
   // Close vector storage
   std::vector<double>* close_vector;
};

int main()
{
   // Set up streams and strings for date parsing
   std::string line;
   std::stringstream ss;
   // Error checking
   //ss.exceptions(std::ios_base::failbit);
   gregorian::date_input_facet * inputFacet = 
         new gregorian::date_input_facet("%e-%b-%y");
   ss.imbue(std::locale(std::locale::classic(), inputFacet));

   ifstream myfile("BZ.csv");
   if(myfile.is_open())
   {
      // Skip the first line by calling getline once.
      std::getline(myfile, line);
      // Create a stock to fill
      Stock mystock;
      while(false == myfile.eof())
      {
         StockSnapshot snapshot;
         gregorian::date date;
         std::vector<std::string> inStrings;
         std::getline(myfile, line);
         boost::algorithm::split(inStrings, line, boost::is_any_of(","));
         // Check to see if we have a single-digit day-of-the-month
         if(inStrings[0][1] == '-')
         {
            // If so, just stream a leading 0
            ss << "0";
         }
         // Input date from file into stringstream
         ss << inStrings[0];
         // Output it into new date object
         ss >> date;
         // Check to make sure we have a valid date
         if(date.is_not_a_date())
         {
            // Skip and go to the next line.
            continue;
         }
         // Set our date with the date object
         snapshot.setDate(date);
         //cout << inStrings[0] << " : " << test << endl;
         // Create a stock snapshot
         // Immediately converts to cents as to avoid later arithmetic errors.
         // Double precision is good enough to hold 2-digit decimal.
         snapshot.setOpen (100 * boost::lexical_cast<double>(inStrings[1]));
         snapshot.setHigh (100 * boost::lexical_cast<double>(inStrings[2]));
         snapshot.setLow  (100 * boost::lexical_cast<double>(inStrings[3]));
         snapshot.setClose(100 * boost::lexical_cast<double>(inStrings[4]));
         //snapshot.print();
         mystock.addSnapshot(snapshot);
      }
      myfile.close();
      // Find our 12-period EMA
      std::vector<double> emas_12;
      mystock.calculateEMASeries(emas_12, 12);
      // Find our 26-period EMA
      std::vector<double> emas_26;
      mystock.calculateEMASeries(emas_26, 26);
      // MACD is 12-period minus the 26-period
      std::vector<double> macd;
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
      std::vector<double> emas_9;
      const StockUtil* stock_util = StockUtil::getInstance();
      stock_util->calculateEMASeries(emas_9, macd, 9);
      BOOST_FOREACH(double i, macd)
      {
         cout << "MACD: " << i << endl;
      }
      BOOST_FOREACH(double i, emas_9)
      {
         cout << "EMA9: " << i << endl;
      }
      
   }
   return EXIT_SUCCESS;
}
