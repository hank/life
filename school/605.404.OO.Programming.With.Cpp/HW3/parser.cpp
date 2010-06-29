#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
// defines 'date' in the current namespace

#include <iostream>
#include <string>
#include <vector>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

// Store all currency values in cents.
class StockSnapshot
{
   std::string snapDate;
   int open;
   int high;
   int low;
   int close;
};

class Stock
{
public:
   std::string name;
   std::vector<StockSnapshot> snapshots;
};


template <typename Iterator>
bool parse_snapshot(Iterator begin, Iterator end, StockSnapshot& snapshot)
{
   using qi::double_;
   using qi::int_;
   using ascii::char_;
   using ascii::space;
   using boost::spirit::omit;

   // Grammar must parse the following:
   // 25-Jun-10,15.13,15.97,14.74,15.57,1560610
   bool r = parse_phrase(begin, end,
      //  Begin grammar
      (   +(char_ - ',')[ref(snapshot.)] >> ','
          >> double_ >> ','
          >> double_ >> ','
          >> double_ >> ','
          >> double_ >> ','
          >> omit[int_]
      ),
      //  End grammar
      space
   );
   if(!r || begin != end) // Fail, no full match
      return false;
   snapshot.
}

int main()
{
    using boost::spirit::ascii::space;
    StockSnapshotParser<std::string::const_iterator> ss_parser;
    std::string str;
    while (getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        StockSnapshot snapshot;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, ss_parser, space, snapshot);
        if (r && iter == end)
        {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "got: " << boost::fusion::as_vector(snapshot) << std::endl;
            std::cout << "\n-------------------------\n";
        }
        else
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }

    }
}
