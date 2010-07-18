// part.h
// Copyright (c) 2010, Erik Gregg
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following
// disclaimer in the documentation and/or other materials provided
// with the distribution.
//
// * Neither the name of Erik Gregg nor the names of his
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Erik Gregg
// Date: Wed Jul 14 21:23:33 EDT 2010
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
