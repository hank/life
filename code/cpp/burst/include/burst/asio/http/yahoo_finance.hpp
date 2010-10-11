// Burst.Asio.HTTP.YahooFinance
// Implements a full-featured interface into Yahoo Finance
// Uses Burst.Asio.HTTP.Client
// Author: Erik Gregg
// Date: Fri Jul 2 02:17:10 EDT 2010
#ifndef Burst_Asio_HTTP_YahooFinance
#define Burst_Asio_HTTP_YahooFinance
#include <iostream>
#include <set>
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
            , functions(default_functions)
            {
               // Initialize with our symbol.
               setSymbol(symbol);
            }

            const std::string& getFunctions()
            {
               return this->functions;
            }

            const std::string& getSymbol()
            {
               return this->symbol;
            }

            enum Function
            {
               Open = 0,
               PreviousClose,
               LENGTH // Hack.
            };

         private:
            void updatePath()
            {
               setPath(std::string("/d/quotes.csv?s=") + 
                       this->symbol + std::string("&f=") +
                       this->functions);
            }

            void setFunctions(const std::string& functions)
            {
               this->functions = functions;
               updatePath();
            }

            void setSymbol(const std::string& symbol)
            {
               this->symbol = symbol;
               updatePath();
            }

            std::string symbol;
            std::set<Function> functions;

            static const std::string default_symbol;
            static const Function default_functions[];
            static const std::string function_symbols[];
         };
         const std::string yahoo_finance::default_symbol = "QQQQ";
         const std::string yahoo_finance::function_symbols[] = {
            "o", "p",
         };
         const yahoo_finance::Function yahoo_finance::default_functions[] = {
            yahoo_finance::Open,
            yahoo_finance::PreviousClose,
         };
      }
   }
}
#endif // Burst_Asio_HTTP_YahooFinance
