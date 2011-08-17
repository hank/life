#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
    io_service ios;

    ip::tcp::endpoint endpoint(tcp::v4(), 55000);
    ip::tcp::acceptor acceptor(ios, endpoint);

    for (;;)
    {
      ip::tcp::iostream stream;
      acceptor.accept(*stream.rdbuf());
      stream << "Foo!" << endl;
    }
}
