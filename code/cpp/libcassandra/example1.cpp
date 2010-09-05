// example1
// Blatantly stolen code from the simple.cc example included in 
// libcassandra
#include <iostream>
using std::cout;
using std::endl;
#include <string>
#include <libcassandra/cassandra_factory.h>
#include <libcassandra/cassandra.h>
#include <libcassandra/keyspace.h>
namespace cass = libcassandra;
#include <boost/foreach.hpp>

static std::string host("127.0.0.1");
static int port = 9160;

int main()
{
   cass::CassandraFactory factory(host, port);
   // Create our client
   std::tr1::shared_ptr<cass::Cassandra> client(factory.create());

   // Get the Cluster Name
   std::string clus_name = client->getClusterName();

   cout << "Cluster Name: " << clus_name << endl;

   std::set<std::string> key_out = client->getKeyspaces();
   BOOST_FOREACH(const std::string& keyspace, key_out)
   {
      cout << "\tKeyspace: " << keyspace << endl;
   }

   std::map<std::string, std::string> tokens = 
                                 client->getTokenMap(false);
   std::map<std::string, std::string>::const_iterator kv_pair = tokens.begin();
   while(kv_pair != tokens.end())
   {
      cout << kv_pair->first << ": " << kv_pair->second << endl;
      ++kv_pair;
   }

   cass::Keyspace* keyspace = client->getKeyspace("drizzle");
   try
   {
      keyspace->insertColumn("Doctor", "Who", "cheers", "More data");
      std::string res = keyspace->getColumnValue("Doctor", "Who", "cheers");
      cout << "Value in column retrieved is: " << res << endl;
      delete keyspace;
      return 0;
   }
   catch(org::apache::cassandra::InvalidRequestException &ire)
   {
      cout << ire.why << endl;
      delete keyspace;
      return 1;
   }
}
