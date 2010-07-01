// Stock Snapshot
// Keeps a single period of snapshot data for a stock.
// Stores the Open, Close, High, and Low values for a stock as well as a given
// Date.  Purely a data class - almost all functionality is implemented at a
// higher level.
// Stores all currency values in cents.
#ifndef StockSnapshot_h
#define StockSnapshot_h
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gregorian = boost::gregorian;

class StockSnapshot
{
public:
   // Default Constructor.  Do nothing.
   StockSnapshot()
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
   operator double();

private:
   gregorian::date date;
   uint32_t open;
   uint32_t high;
   uint32_t low;
   uint32_t close;
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
