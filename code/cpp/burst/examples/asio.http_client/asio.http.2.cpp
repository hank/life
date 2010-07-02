// Burst.Asio.HTTP.Client Example 2
// Shows how to use the class with special parameters
#include <iostream>
using std::cout;
using std::endl;
#include "burst/asio/http/client.hpp"
int main(int argc, char* argv[])
{
   try
   {
      // Initialize an HTTP client
      burst::asio::http::client client("download.finance.yahoo.com",
         "/d/quotes.csv?s=QQQQ&f=l1"
      );
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
