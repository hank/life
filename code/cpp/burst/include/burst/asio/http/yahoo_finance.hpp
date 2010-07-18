// Burst.Asio.HTTP.YahooFinance
// Implements a full-featured interface into Yahoo Finance
// Uses Burst.Asio.HTTP.Client
// Author: Erik Gregg
// Date: Fri Jul 2 02:17:10 EDT 2010
#ifndef Burst_Asio_HTTP_YahooFinance
#define Burst_Asio_HTTP_YahooFinance
#include <string>
#include <burst/asio/http/client.hpp>
namespace burst
{
   namespace asio
   {
      namespace http
      {
         class yahoo_finance : public client
         {
         public:
            explicit yahoo_finance(
                        const std::string& symbol = default_symbol)
            : client("download.finance.yahoo.com")
            {
               // Initialize with our symbol.
               setSymbol(symbol);
            }

            void setSymbol(const std::string& symbol)
            {
               this->symbol = symbol;
               setPath(std::string("/d/quotes.csv?s=") + 
                       this->symbol + 
                       std::string("&f=l1"));
            }

         private:
            std::string symbol;

            static const std::string default_symbol;
         };
         const std::string yahoo_finance::default_symbol = "QQQQ";
      }
   }
}
#endif // Burst_Asio_HTTP_YahooFinance
