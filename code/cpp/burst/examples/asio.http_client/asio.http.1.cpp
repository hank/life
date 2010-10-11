// Burst.Asio.HTTP.Client Example 1
// Shows how to use the class with its default parameters.
#include <iostream>
using std::cout;
using std::endl;
#include "burst/asio/http/client.hpp"
int main(int argc, char* argv[])
{
   try
   {
      // Initialize a boost.org HTTP client
      burst::asio::http::client client;
      client.print_request(cout);
      // Send the request to boost.org
      client.send_request();
      // Print the response into the cout stream
      client.print_response(cout);
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }
}
