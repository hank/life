// Burst.Asio.HTTP.YahooFinance Example
// Use Yahoo Finance API to retreive stock quotes
#include <iostream>
using std::cout;
using std::endl;
#include "burst/asio/http/yahoo_finance.hpp"
int main(int argc, char* argv[])
{
   try
   {
      // Initialize an HTTP client
      burst::asio::http::yahoo_finance client;
      // Send the request
      client.send_request();
      // Print the response into the cout stream
      client.print_response(cout);
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }
}
