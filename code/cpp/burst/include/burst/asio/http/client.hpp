// Burst.Asio.HTTP.Client
// Implements a simple web client with an extremely simple API
// Uses Boost.Asio's awesome HTTP library.
// Author: Erik Gregg
// Date: Fri Jul 2 00:49:06 EDT 2010
// See top-level LICENSE file for licensing information
#ifndef Burst_Asio_HTTP_Client
#define Burst_Asio_HTTP_Client
#include <boost/asio.hpp>
namespace burst
{
   namespace asio
   {
      namespace http
      {
         class client
         {
         public:
            // Three parameter constructor.  Allows user to set host, path, and
            // user-agent
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

            virtual ~client()
            {
               delete this->stream;
            }

            // Print Request is just an alias for Print GET request
            bool print_request(std::ostream& stream) const
            { 
               return print_get_request(stream); 
            }

            // Print GET Request sends the request to be generated to the 
            // given stream
            bool print_get_request(std::ostream& stream) const
            { 
               stream << "GET " << getPath() << " HTTP/1.0\r\n";
               send_headers(stream);
               stream << "\r\n";
               stream.flush();
               return true;
            }

            // Print POST Request sends the request to be generated to the
            // given stream with post data
            bool print_post_request(std::ostream& stream, 
                                    const std::string& post_data) const
            { 
               stream << "POST " << getPath() << " HTTP/1.0\r\n";
               send_headers(stream);
               stream << "\r\n" << post_data;
               stream.flush();
               return true;
            }

            // Send Request is just an alias for Send GET request
            bool send_request() const
            { 
               return send_get_request(); 
            }

            // Send GET request explicitly sends a GET
            bool send_get_request() const
            {
               return print_get_request(*(this->stream));
            }

            // Send POST Request posts some post data to the server
            bool send_post_request(const std::string& post_data) const
            {
               return print_post_request(*(this->stream), post_data);
            }

            // Print Response outputs the response to the given stream
            void print_response(std::ostream& stream) const
            {
               std::string response_line;
               this->stream->receive(response_line);
               stream << response_line;
            }


            // Getters/setters
            const std::string getPath() const
            {
               return this->path;
            }
            const std::string getHost() const
            {
               return this->host;
            }
            const std::string getUserAgent() const
            {
               return this->user_agent;
            }

            const std::string getAccept() const
            {
               return this->accept;
            }

            void setPath(const std::string& path)
            {
               this->path = path;
            }
            void setHost(const std::string& host)
            {
               this->host = host;
            }
            void setUserAgent(const std::string& user_agent)
            {
               this->user_agent = user_agent;
            }

            void setAccept (const std::string& accept)
            {
               this->accept = accept;
            }

         protected:
            // Send HTTP headers sends all the HTTP headers down the stream
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
            std::string path;
            std::string host;
            std::string user_agent;
            std::string accept;
            boost::asio::ip::tcp::iostream* stream;
         };
         // Set up our statics
      }
   }
}
#endif // Burst_Asio_HTTP_Client
