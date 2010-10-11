// Simple Boost.Spirit.Qi Example
//   Parses a comma delimited list of integers into a vector of integers.
//   Skips whitespace properly.
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
#include <algorithm>

#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;
#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

int main()
{
  using boost::spirit::int_;
  using qi::_1;
  using qi::phrase_parse;
  using boost::spirit::ascii::space;
  using phoenix::ref;
  string input("1234, 3456,7890");
  string::iterator begin = input.begin();
  string::iterator end = input.end();
  std::vector<int> result;
  phrase_parse(begin, end, 
               // Begin Parser
               (int_       [push_back(ref(result), _1)]
                  >> *(','
                  >> int_  [push_back(ref(result), _1)]
                      )
               ),
               // End Parser
               space);

  // Iterate through the vector using Boost.ForEach
  BOOST_FOREACH(int &i, result)
  {
    cout << i << endl;
  }
}
