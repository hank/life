// hugeint.h
// Contains HugeInt Class
#ifndef HugeInt_h
#define HugeInt_h
#include <string>
using std::string;
#include <boost/cstdint.hpp>

// Huge integer class
// Allows arbitrary length integers and allows arithmetic manipulation
// of them.  The size can be defined at compile time using the DEFAULT_LENGTH
// constant.  All basic arithmetic is implemented.
// Copyright (c) 2010, Erik Gregg
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
//     * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above
//     copyright notice, this list of conditions and the following
//     disclaimer in the documentation and/or other materials provided
//     with the distribution.
// 
//     * Neither the name of Erik Gregg nor the names of his
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
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
// Date: Tue Jun 15 00:18:02 EDT 2010
class HugeInt
{
   public:
      // Default constructor - set a zero
      HugeInt();
      // 1 or 2 parameter int constructor
      HugeInt(const uint64_t& i);
      // 1 parameter string constructor
      HugeInt(const string& s);
      // Copy constructor
      HugeInt(const HugeInt& from);

      // Initialize the instance with a string
      void init(const string& s);
      // Initialize the instance with an integer
      void init(uint64_t i);
      // Zero out the instance
      void zero();
      // HugeInt equality operator
      bool operator == (const HugeInt& right) const;
      // Integer equality operator
      bool operator == (const uint64_t& right) const;
      // String equality operator
      bool operator == (const string& right) const;

      // HugeInt Not Equal operator
      bool operator != (const HugeInt& right) const;
      // Integer Not Equal operator
      bool operator != (const uint64_t& right) const;

      // HugeInt Greater Than operator
      bool operator > (const HugeInt& right) const;
      // Integer Greater Than operator
      bool operator > (const uint64_t& right) const;
      // HugeInt Greater Than or Equal operator
      bool operator >= (const HugeInt& right) const;
      // Integer Greater Than or Equal operator
      bool operator >= (const uint64_t& right) const;

      // Integer Not Equal operator
      bool operator < (const HugeInt& right) const;
      // Integer Not Equal operator
      bool operator < (const uint64_t& right) const;
      // HugeInt Not Equal operator
      bool operator <= (const HugeInt& right) const;
      // HugeInt Not Equal operator
      bool operator <= (const uint64_t& right) const;

      // Integer assignment operator
      HugeInt& operator = (const uint64_t& right);
      // String assignment operator
      HugeInt& operator = (const string& right);

      // Array Index operator
      uint8_t& operator [](const uint16_t idx);
      // Const Array Index operator
      const uint8_t& operator [](const uint16_t idx) const;

      // HugeInt addition assignment
      HugeInt& operator += (const HugeInt& right);
      // HugeInt addition 
      HugeInt operator + (const HugeInt& right) const;
      // Integer addition assignment
      HugeInt& operator += (const uint64_t& right);
      // Integer addition
      HugeInt operator + (const uint64_t& right) const
      {
         return *this + HugeInt(right);
      }
      // Increment
      HugeInt& operator ++ (); // Prefix
      // Increment
      HugeInt operator ++ (int); // Postfix

      // HugeInt subtraction assignment
      HugeInt& operator -= (const HugeInt& right);
      // HugeInt subtraction
      HugeInt operator - (const HugeInt& right) const;
      // Integer subtraction assignment
      HugeInt& operator -= (const uint64_t& right);
      // Integer subtraction 
      HugeInt operator - (const uint64_t& right) const
      {
         return *this - HugeInt(right);
      }
      // Decrement
      HugeInt& operator -- (); // Prefix
      // Decrement
      HugeInt operator -- (int); // Postfix

      // HugeInt multiplication
      HugeInt operator * (const HugeInt& right) const;
      // Integer multiplication
      HugeInt operator * (const uint64_t& right) const;
      // HugeInt multiplication-assign
      HugeInt& operator *= (const HugeInt& right);
      // Integer multiplication-assign
      HugeInt& operator *= (const uint64_t& right);

      // Right Shift Assign
      HugeInt& operator >>= (const uint64_t& amount);
      // Right Shift
      HugeInt operator >> (const uint64_t& amount) const;

      // Left Shift Assign
      HugeInt& operator <<= (const uint64_t& amount);
      // Left Shift
      HugeInt operator << (const uint64_t& amount) const;

      // HugeInt division
      HugeInt operator / (const HugeInt& right) const;
      // Integer division
      HugeInt operator / (const uint64_t& right) const;
      // HugeInt division-assign
      HugeInt& operator /= (const HugeInt& right);
      // Integer division-assign
      HugeInt& operator /= (const uint64_t& right);

      // String cast operator
      operator string() const;

      // Size function
      // Give the number of digits in the current decimal representation
      uint16_t size() const;

   private:
      // Constant size of the decimal field for all objects
      static const uint16_t DEFAULT_SIZE = 50;
      // Decimal Representation
      uint8_t integerField[DEFAULT_SIZE];
};
#endif // HugeInt_h
