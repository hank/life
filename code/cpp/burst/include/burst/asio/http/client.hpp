// Burst.Asio.HTTP.Client
// Implements a simple web client with an extremely simple API
// Uses Boost.Asio's awesome HTTP library.
// Author: Erik Gregg
// Date: Fri Jul 2 00:49:06 EDT 2010
// See top-level LICENSE file for licensing information
#ifndef Burst_Asio_HTTP_Client
#define Burst_Asio_HTTP_Client
#include <boost/asio.hpp>
#include <iostream>
// Namespace: burst
// Framework riding on the shoulders of boost
namespace burst
{
   // Namespace: asio
   // Asychronous I/O
   namespace asio
   {
      // Namespace: http
      // HTTP bindings
      namespace http
      {
        // Class: client
        // HTTP client class for Asynchronous I/O
         class client
         {
         public:
            // Constructor: client
            // Allows user to set host, path, and user-agent.
            //
            // Parameters:
            // host - The hostname to connect to.
            // path - The path to request.
            // user_agent - The User-Agent to claim we are.
            explicit client(const std::string& host = "www.boost.org", 
                      const std::string& path = "/",
                      const std::string& user_agent = "Boost.Asio.HttpClient")
            : path(path)
            , host(host)
            , user_agent(user_agent)
            , accept("")
            {
               this->stream = 
                  new boost::asio::ip::tcp::iostream(host, "http");
            }

            // Destructor: ~client
            virtual ~client()
            {
               delete this->stream;
            }

            // Function: print_request
            // Print Request is just an alias for Print GET request.
            bool print_request(std::ostream& stream) const
            { 
               return print_get_request(stream); 
            }

            // Function: print_get_request
            // Print GET Request sends the request to be generated to the 
            // given stream.
            bool print_get_request(std::ostream& stream) const
            { 
               stream << "GET " << getPath() << " HTTP/1.0\r\n";
               send_headers(stream);
               stream << "\r\n";
               stream.flush();
               return true;
            }

            // Function: print_post_request
            // Print POST Request sends the request to be generated to the
            // given stream with post data.
            //
            // Parameters:
            // stream - an output stream
            // post_data - data to be included in the body of the request
            bool print_post_request(std::ostream& stream, 
                                    const std::string& post_data) const
            { 
               stream << "POST " << getPath() << " HTTP/1.0\r\n";
               send_headers(stream);
               stream << "\r\n" << post_data;
               stream.flush();
               return true;
            }

            // Function: send_request
            // Send Request is just an alias for Send GET request.
            bool send_request() const
            { 
               return send_get_request(); 
            }

            // Function: send_get_request
            // Send GET request explicitly sends a GET.
            bool send_get_request() const
            {
               std::cout << path;
               *(this->stream) << "GET " << path << " HTTP/1.0\r\n"
                      << "Host: " << host << "\r\n"
                      << "User-Agent: " << user_agent << "\r\n"
                      << "\r\n";
               this->stream->flush();
               return print_get_request(*(this->stream));
            }

            // Function: send_post_request
            // Send POST Request posts some post data to the server
            bool send_post_request(const std::string& post_data) const
            {
               return print_post_request(*(this->stream), post_data);
            }

            // Group: Output

            // Function: print_response 
            // Outputs the response to the given stream.
            void print_response(std::ostream& stream) const
            {
               std::string response_line;
               this->stream->receive(response_line);
               stream << response_line;
            }

            // Function: print_response _content
            // Outputs the response content to the given stream.
            void print_response_content(std::ostream& stream)
            {
               std::string response_line;
               bool output = false;
               while(false == this->stream->eof()) {
                  std::getline(*(this->stream), response_line);
                  if(output) stream << response_line << endl;
                  else {
                     if(response_line == "\r\n") output = true;
                  }
               }
            }


            // Group: Getters

            // Function: getPath
            // Returns the HTTP Path.
            const std::string getPath() const
            {
               return this->path;
            }
            // Function: getHost
            // Returns the HTTP Host field.
            const std::string getHost() const
            {
               return this->host;
            }
            // Function: getUserAgent
            // Returns the HTTP User-Agent field.
            const std::string getUserAgent() const
            {
               return this->user_agent;
            }
            // Function: getAccept
            // Returns the HTTP Accept field.
            const std::string getAccept() const
            {
               return this->accept;
            }

            // Group: Setters

            // Function: setPath
            // Sets the HTTP Path.
            void setPath(const std::string& path)
            {
               this->path = path;
            }
            // Function: setHost
            // Sets the HTTP Host field.
            void setHost(const std::string& host)
            {
               this->host = host;
            }
            // Function: setUserAgent
            // Sets the HTTP User-Agent field.
            void setUserAgent(const std::string& user_agent)
            {
               this->user_agent = user_agent;
            }
            // Function: setAccept
            // Sets the HTTP Accept field.
            void setAccept (const std::string& accept)
            {
               this->accept = accept;
            }

         protected:
            // Function: send_headers
            // Send HTTP headers sends all the HTTP headers down the stream.
            void send_headers(std::ostream& stream) const
            {
              stream 
                  << "Host: " << getHost() << "\r\n"
                  << "User-Agent: " << getUserAgent() << "\r\n"
                  << "Connection: close\r\n";
               if(this->accept != "")
               {
                  stream << getAccept();
               }
            }

         private:
            // Group: Variables

            // Variable: path
            std::string path;
            // Variable: host
            std::string host;
            // Variable: user_agent
            std::string user_agent;
            // Variable: accept
            std::string accept;
            // Variable: stream
            // Set in the constructor to Boost's HTTP Asio.
            boost::asio::ip::tcp::iostream* stream;
         };
      }
   }
}
#endif // Burst_Asio_HTTP_Client
