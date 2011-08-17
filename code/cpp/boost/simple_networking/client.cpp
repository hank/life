#include <iostream>
#include <string>
using namespace std;
#include <boost/asio.hpp>
using namespace boost::asio::ip;

int main()
{
    tcp::iostream stream("localhost", "55000");
    if (!stream)
    {
      // Can't connect.
      fprintf(stderr, "Error: Could not connect.\n");
      return 1;
    }
    // Print what we get back
    cout << stream.rdbuf();
    return 0;
}
