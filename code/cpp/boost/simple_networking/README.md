# Simple Boost.Asio Client/Server
This is a neat little example of an extremely simple Boost.Asio client and server.  Perhaps someone will find it useful.  Threading would be nice if you want multiple simultaneous clients.  Boost.Thread would help with that.

## Building
Get dependencies

    sudo apt-get install libboost-dev libboost-system-dev build-essential
Then

    make

## Running
Run the server:

    ./server

Then run the client:

    ./client

**Tada!**

## Information Sources
[Boost.Asio Iostreams Examples](http://www.boost.org/doc/libs/1_42_0/doc/html/boost_asio/examples.html#boost_asio.examples.iostreams)
