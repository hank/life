// Burst.Asio.HTTP.Client
// Implements a simple web client with an extremely simple API
// Uses Boost.Asio's awesome HTTP library.
// Author: Erik Gregg
// Date: Fri Jul 2 00:49:06 EDT 2010
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
            explicit client(const std::string& host = default_host, 
                            const std::string& path = default_path,
                            const std::string& user_agent = default_user_agent)
            : path(path)
            , host(host)
            , user_agent(user_agent)
            {
               this->stream = new boost::asio::ip::tcp::iostream(host, "http");
            }

            ~client()
            {
               delete this->stream;
            }

            bool send_request()
            {
               *(this->stream) << "GET " << path << " HTTP/1.0\r\n"
                      << "Host: " << host << "\r\n"
                      << "User-Agent: " << user_agent << "\r\n"
                      << "\r\n";
               this->stream->flush();
            }

            void print_response(std::ostream& stream)
            {
               std::string response_line;
               while(false == this->stream->eof()) {
                  std::getline(*(this->stream), response_line);
                  stream << response_line << endl;
               }
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

         private:
            std::string path;
            std::string host;
            std::string user_agent;
            boost::asio::ip::tcp::iostream* stream;
            static const std::string default_path;
            static const std::string default_host;
            static const std::string default_user_agent;
         };
         const std::string client::default_path = "/";
         const std::string client::default_host = "www.boost.org";
         const std::string client::default_user_agent = 
                                               "Burst.Asio.HttpClient";
      }
   }
}
#endif // Burst_Asio_HTTP_Client
