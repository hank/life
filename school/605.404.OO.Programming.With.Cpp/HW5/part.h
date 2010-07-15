// part.h
#ifndef Part_H
#define Part_H
#include <boost/throw_exception.hpp>
#include <boost/functional/hash.hpp>
// Exception class for Part Constructor
// Throws if Part fails to parse its input.
class BadPartException : public boost::exception, public std::exception
{
   // Intentionally blank
   // Using the standard boost::exception properties
};

// Part class
// Defines a simple part that is an ingredient in a Kit
// The part is basically a line item in a kit description,
// and is meant to be linked with a kit in some form.
class Part
{
   public:
      // Default constructor.  Used for creating search parts.
      Part()
      {}
      // Single-param string constructor
      // Parses an entire line of CSV input in the following format:
      // quantity,number,name
      Part(const std::string& line) throw(BadPartException);
      // Get the name
      std::string getName() const;
      // Set the name
      void setName(const std::string& name);
      // Get the Part Number
      std::string getNumber() const;
      // Set the Part Number
      void setNumber(const std::string& number);
      // Get the quantity
      int getQuantity() const;
      // Set the quantity
      void setQuantity(const uint64_t& quantity);

   private:
      std::string name;
      std::string number;
      int quantity;
};

// Function Definitions
inline std::string Part::getName() const
{
   return this->name;
}

inline void Part::setName(const std::string& name)
{
   this->name = name;
}

inline std::string Part::getNumber() const
{
   return this->number;
}

inline void Part::setNumber(const std::string& number)
{
   this->number = number;
}

inline int Part::getQuantity() const
{
   return this->quantity;
}

inline void Part::setQuantity(const uint64_t& quantity)
{
   this->quantity = quantity;
}

// Global Overloads
// Equality
// Only looks at the Part Number
inline bool operator==(const Part& p1, const Part& p2)
{
   return p1.getNumber() == p2.getNumber();
}

// Hashing
// Only looks at the Part Number
inline std::size_t hash_value(const Part& part)
{
   boost::hash<std::string> hasher;
   return hasher(part.getNumber());
}

// Stream Output
inline std::ostream& operator<< (std::ostream &stream, const Part& part)
{
   stream << "Part { "
          << part.getNumber() << ", "
          << part.getName() << " }";

   return stream;
}


#endif // Part_H
