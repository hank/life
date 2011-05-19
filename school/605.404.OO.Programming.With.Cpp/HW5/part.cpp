// part.cpp
// Defines the implementation of Part
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/throw_exception.hpp>
#include <locale>

#include "part.h"

// 1-param Constructor
Part::Part(const std::string& line) throw(BadPartException)
{
   // Simple validation
   // Line must have characters
   // and first ones need to be numbers
   // Short-circuits to avoid dereferencing line[0] when invalid
   if(line.length() <= 1 ||
         !std::isdigit(line[0])
     )
   {
      BOOST_THROW_EXCEPTION(BadPartException());
   }
   // Use Boost.Tokenizer to parse the line
   boost::tokenizer< boost::escaped_list_separator< char > > tok(line);
   boost::tokenizer< boost::escaped_list_separator< char > >::iterator 
      iter = tok.begin();

   try
   {
      // First field is Quantity
      setQuantity(boost::lexical_cast<int>(*iter++));
   }
   catch(boost::bad_lexical_cast& exception)
   {
      // We've tried to do a bad cast.
      // Simply throw our custom exception
      BOOST_THROW_EXCEPTION(BadPartException());
   }
   // Next is the part number
   setNumber(*iter++);
   // Finally, set the name
   // Trim off any whitespace at the end
   std::string trimmed_name = *iter++;
   boost::trim(trimmed_name);
   setName(trimmed_name);
}

