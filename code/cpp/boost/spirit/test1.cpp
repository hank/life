// Simple Boost.Spirit.Qi Example
//   Parses the string "1234" into the integer 1234 and prints it.
#include <iostream>
using std::cout;
using std::endl;
#include <string>

#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/support/ascii.hpp>
#include <boost/spirit/home/support/placeholders.hpp>
#include <boost/spirit/home/qi/meta_grammar.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace mpl = boost::mpl;
namespace phoenix = boost::phoenix;

int main()
{
  std::string input("1234");
  std::string::iterator begin = input.begin();
  std::string::iterator end = input.end();
  int result = 0;
  qi::phrase_parse(begin, end, 
                   boost::spirit::int_, 
                   result,
                   boost::spirit::ascii::space);
  cout << result << endl;
}
