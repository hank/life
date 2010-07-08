// hugeint.cpp
// Contains HugeInt Implementation
// Implementation Notes:
//   - Multiplication and Division make heavy use of left and right shift.
//   - Left and right shift multiply and divide by 10 (truncating)
//   - This implementation is several times faster than the basic schoolbook
//     kind.
//
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
// Date: Thu Jul  8 01:51:16 EDT 2010

// Needed for memset and memcpy
#include <string.h>

#include <string>
using std::string;
#include "hugeint.h"

// Default constructor
HugeInt::HugeInt()
{
   zero();
}

// Int constructor
HugeInt::HugeInt(const uint64_t& i)
{
   // Reset
   zero();
   init(i);
}

// String constructor
HugeInt::HugeInt(const string& s)
{
   zero();
   init(s);
}

// Copy constructor
HugeInt::HugeInt(const HugeInt& from)
{
   memcpy(integerField, from.integerField, DEFAULT_SIZE);
}

// Zeroing function - just initializes array to 0
void HugeInt::zero()
{
   // Set to 255 (denotes empty)
   memset(this->integerField, 255, DEFAULT_SIZE);
   // Set last value to 0
   this->integerField[DEFAULT_SIZE - 1] = 0;
}

// Initialize the instance with a string
// Expects a clean instance!
void HugeInt::init(const string& s)
{
   // Fill in integerField
   int offset = DEFAULT_SIZE - s.length();
   if(offset < 0)
   {
      // Overflow?  Set to 0.
      zero();
   }
   else
   {
      for(uint16_t j = 0; j < s.length(); j++)
      {
         // Add the characters
         if(isdigit(s[j]))
         {
            // Fill in with non-ASCII value of numeral
            this->integerField[offset + j] = s[j] - 0x30;
         }
      }
   }
}

// Initialize the instance with an integer
// Expects a clean instance!
// Copies i
void HugeInt::init(uint64_t i)
{
   // Fill in integerField
   uint16_t j = DEFAULT_SIZE - 1;
   // Special case for 0
   if(0 == i)
   {
      (*this)[j] = 0;
   }
   else
   {
      while(i > 0 && j > 0)
      {
         // Take last base-10 digit
         (*this)[j] = i % 10;
         // Remove last base-10 digit
         i /= 10;
         // Move back
         j--;
      }
   }
}

// HugeInt equality operator
bool HugeInt::operator == (const HugeInt& right) const
{
   // Check if they're even the same size
   if(right.size() != this->size()) 
   {
      return false;
   }
   uint16_t last_index = DEFAULT_SIZE - 1;
   for(int i = last_index; i >= 0; i--)
   {
      if((*this)[i] != right[i]) return false;
   }
   return true;
}

// Integer equality operator
bool HugeInt::operator == (const uint64_t& right) const
{
   return *this == HugeInt(right);
}

// HugeInt string equality operator
bool HugeInt::operator == (const string& right) const
{
   return *this == HugeInt(right);
}

// Integer assignment operator
HugeInt& HugeInt::operator = (const uint64_t& right) 
{
   // Groom space for new data
   memset(this->integerField, 255, DEFAULT_SIZE);
   // Initialize
   init(right);
   return *this;
}

// Char* assignment operator
HugeInt& HugeInt::operator = (const string& right) 
{
   // Groom space for new data
   memset(this->integerField, 255, DEFAULT_SIZE);
   // Initialize
   init(right);
   return *this;
}

// HugeInt addition-assign
HugeInt& HugeInt::operator += (const HugeInt& right)
{
   *this = *this + right;
   return *this;
}

// Integer addition-assign
HugeInt& HugeInt::operator += (const uint64_t& right)
{
   *this = *this + right;
   return *this;
}

// HugeInt addition
HugeInt HugeInt::operator + (const HugeInt& right) const
{
   const HugeInt* to_add;
   HugeInt dest;
   if(right.size() > size())
   {
      // Right side is bigger - Copy it
      dest = HugeInt(right);
      to_add = this;
   }
   else
   {
      // Left is bigger or sizes are equal.  Copy this
      dest = HugeInt(*this);
      to_add = &right;
   }
   // From the end of the integers, add and carry
   uint8_t result;
   for(uint16_t i = 1; i <= to_add->size(); i++)
   {
      result = (*to_add)[DEFAULT_SIZE - i];
      result += dest[DEFAULT_SIZE - i];
      if(result > 9) 
      {
         // Check for overflow
         if(i + 1 == DEFAULT_SIZE)
         {
            // We've gone over.
            dest = 0;
            break;
         }
         else
         {
            // Set previous value to 1 if it's uninitialized.
            if(255 == dest[DEFAULT_SIZE - i - 1])
            {
               dest[DEFAULT_SIZE - i - 1] = 1;
            }
            else
            {
               if(DEFAULT_SIZE == i + 2)
               {
                  // Overflow
                  dest = 0;
                  break;
               }
               // If it's already 9, make it 0 and carry
               else if(9 == dest[DEFAULT_SIZE - i - 1])
               {
                  // Carry it up until we hit a non-9
                  uint16_t j = DEFAULT_SIZE - i - 1;
                  uint16_t array_start = 0; // First index in the array
                  do
                  {
                     dest[j] = 0;
                     --j;
                  } while(dest[j] == 9 && j > array_start);
                  // If we're at the front of the array, check if we're
                  // overflowing
                  if(j == array_start)
                  {
                     if(dest[j] == 9)
                     {
                        // We're at maximum
                        dest = 0;
                        break;
                     }
                     else
                     {
                        ++dest[j];
                     }
                  }
                  else
                  {
                     // Set to 1 if 255
                     if(255 == dest[j])
                     {
                        dest[j] = 1;
                     }
                     // Otherwise just increment
                     else
                     {
                        ++dest[j];
                     }
                  }
               }
               // Otherwise, just increment
               else
               {
                  dest[DEFAULT_SIZE - i - 1]++;
               }
            }
         }
      }
      dest[DEFAULT_SIZE - i] = result % 10;
   }
   return dest;
}

// Const Indexing
const uint8_t& HugeInt::operator[](const uint16_t idx) const
{
   return this->integerField[idx];
}

// Indexing
uint8_t& HugeInt::operator[](const uint16_t idx)
{
   return this->integerField[idx];
}

// HugeInt subtraction
HugeInt HugeInt::operator - (const HugeInt& right) const
{
   HugeInt to_return = HugeInt(*this);
   // From the end of the integers, add and carry
   for(int i = 1; i < right.size() + 1; i++)
   {
      uint16_t current_index = DEFAULT_SIZE - i - 1;
      uint16_t last_index = DEFAULT_SIZE - 1;
      int8_t result = to_return[DEFAULT_SIZE - i];
      result -= right[DEFAULT_SIZE - i];
      if(result < 0) 
      {
         // Decrement previous value
         // If uninitialized, we've gone negative.
         if(255 == to_return[current_index])
         {
            to_return = 0;
            break;
         }
         else
         {
            // Loop until we decrement something
            // j is one before the current value
            uint16_t j = current_index;
            for(; j > 0; j--)
            {
               // If we hit a 0, just change to a 9 and keep iterating
               if(to_return[j] == 0)
               {
                  to_return[j] = 9;
               }
               else
               {
                  // Otherwise, just decrement
                  // If the value is now 0, and it's the Most Significant
                  // Digit, set it to uninitialized.
                  --to_return[j];
                  // Check if we're the first digit
                  // or if the previous digit is uninitialized
                  if(0 == to_return[j] &&
                     ( 0 == j ||
                       255 == to_return[j-1]
                     )
                    )
                  {
                     // If so, set to uninitialized
                     to_return[j] = 255;
                  }
                  break;
               }
            }
            // Make sure we haven't depleted the array
            if(0 == j)
            {
               to_return = 0;
               break;
            }
         }
         result += 10;
         to_return[DEFAULT_SIZE - i] = result % 10;
      }
      else
      {
         to_return[DEFAULT_SIZE - i] = result;
      }
   }
   return to_return;
}

// Integer Greater-than or Equal
bool HugeInt::operator >= (const uint64_t& right) const
{
   return *this >= HugeInt(right);
}

// HugeInt Greater-than or Equal
bool HugeInt::operator >= (const HugeInt& right) const
{
   bool result = false;
   if(*this == right)
   {
      result = true;
   }
   else if(*this > right)
   {
      result = true;
   }
   return result;
}

// Integer Less-than or Equal
bool HugeInt::operator <= (const uint64_t& right) const
{
   return HugeInt(right) >= *this;
}

// HugeInt Less-than or Equal
bool HugeInt::operator <= (const HugeInt& right) const
{
   return right >= *this;
}

// Integer Less-than
bool HugeInt::operator < (const uint64_t& right) const
{
   return HugeInt(right) > *this;
}

// HugeInt Less-than
bool HugeInt::operator < (const HugeInt& right) const
{
   return right > *this;
}

// Integer Greater-than
bool HugeInt::operator > (const uint64_t& right) const
{
   return *this > HugeInt(right);
}

// HugeInt Greater-than
bool HugeInt::operator > (const HugeInt& right) const
{
   bool result = false;
   for(int i = 0; i < DEFAULT_SIZE; ++i)
   {
      if((*this)[i] != right[i]) 
      {
         // See if one is uninitialized
         if(right[i] == 255)
         {
            result = true;
         }
         else if((*this)[i] == 255)
         {
            result = false;
         }
         else
         {
            result = (*this)[i] > right[i];
         }
         // We're done.  Break out of loop
         break;
      }
   }
   return result;
}

// HugeInt Not Equal
bool HugeInt::operator != (const HugeInt& right) const
{
   return (*this == right) == false;
}

// Integer Not Equal
bool HugeInt::operator != (const uint64_t& right) const
{
   return (*this == HugeInt(right)) == false;
}

// Integer Minus-Equal
HugeInt& HugeInt::operator -= (const uint64_t& right)
{
   *this = *this - right;
   return *this;
}

// HugeInt Minus-Equal
HugeInt& HugeInt::operator -= (const HugeInt& right)
{
   *this = *this - right;
   return *this;
}

// HugeInt Decrement
HugeInt& HugeInt::operator -- () // Prefix
{
   // Simply Subtract
   *this -= 1;
   return *this;
}

// HugeInt Decrement
HugeInt HugeInt::operator -- (int)  // Postfix
{
   // Copy, decrement, return old
   HugeInt to_return = HugeInt(*this);
   *this -= 1;
   return to_return;
}

// HugeInt Increment
HugeInt& HugeInt::operator ++ () // Prefix
{
   // Simply Add
   *this += 1;
   return *this;
}

// HugeInt Increment
HugeInt HugeInt::operator ++ (int)  // Postfix
{
   // Copy, increment, return old
   HugeInt to_return = HugeInt(*this);
   *this += 1;
   return to_return;
}

// Multiplication
HugeInt HugeInt::operator * (const HugeInt& right) const
{
   HugeInt to_return = HugeInt(*this);
   HugeInt rcopy = HugeInt(right);
   if(rcopy >= 10)
   {
      while(rcopy >= 10)
      {
         rcopy >>= 1;
         to_return <<= 1;
      }
   }
   // Re-initialize rcopy
   rcopy = right;
   // Define an adder
   HugeInt adder = to_return;
   to_return = 0;

   uint16_t first_index = DEFAULT_SIZE - rcopy.size();
   uint16_t last_index = DEFAULT_SIZE - 1;
   int i = first_index; 
   while(i <= last_index)
   {
      // For each place, add the adder N times
      // where N is the current digit
      if(rcopy[i] != 0)
      {
         while(rcopy[i]--)
         {
            to_return += adder;
         }
      }
      adder >>= 1;
      // Adder is 10x less now
      ++i;
   }
   return to_return;
}

// Integer Multiplication
HugeInt HugeInt::operator * (const uint64_t& right) const
{
   return *this * HugeInt(right);
}

// Multiplication-Assign
HugeInt& HugeInt::operator *= (const HugeInt& right)
{
   *this = *this * right;
   return *this;
}

// Multiplication-Assign
HugeInt& HugeInt::operator *= (const uint64_t& right)
{
   *this = *this * HugeInt(right);
   return *this;
}

// Right Shift-Assign
HugeInt& HugeInt::operator >>= (const uint64_t& amount)
{
   // Handle < 10
   if(size() == 1)
   {
      *this = 0;
   }
   else
   {
      // Iterate backwards skipping the last digit,
      // which is truncated
      uint16_t second_to_last_index = DEFAULT_SIZE - 2;
      uint16_t first_index = DEFAULT_SIZE - size() - 1;
      for(int i = second_to_last_index; i >= first_index; i--)
      {
         (*this)[i+1] = (*this)[i];
      }
      // Fill in first space with 255
      (*this)[first_index] = 255;
   }
   return *this;
}

// Right Shift
HugeInt HugeInt::operator >> (const uint64_t& amount) const
{
   HugeInt result(*this);
   result >>= amount;
   return result;
}

// Left Shift-Assign
HugeInt& HugeInt::operator <<= (const uint64_t& amount)
{

   // Iterate forwards
   uint16_t last_index = DEFAULT_SIZE - 1;
   uint16_t first_index = DEFAULT_SIZE - size() - 1;
   if(0 == first_index)
   {
      // If top truncation occurs, return 0 for overflow condition
      *this = 0;
   }
   else
   {
      for(int i = first_index; i <= last_index; i++)
      {
         // Copy next byte over
         (*this)[i-1] = (*this)[i];
      }
      // Set last byte to 0
      (*this)[last_index] = 0;
   }
   return *this;
}

// Left Shift
HugeInt HugeInt::operator << (const uint64_t& amount) const
{
   HugeInt result(*this);
   result <<= amount;
   return result;
}

// Division
HugeInt HugeInt::operator / (const HugeInt& right) const
{
   HugeInt result(1);
   // First, make sure divisor is less than this
   if(right > *this)
   {
      result = 0;
   }
   else
   {
      // Solve by iterating by powers of 10
      // Use the right shift operator to divide by 10
      HugeInt copy(*this);
      while(right < copy)
      {
        copy >>= 1;
        result <<= 1;
      }
      // At this point, we've gone 1 iteration past where we need to.
      // Divide by 10 to fix this.
      result >>= 1;

      // Now that we have the right 10's place, find each digit iteratively
      uint16_t first_index = DEFAULT_SIZE - result.size();
      uint16_t last_index = DEFAULT_SIZE - 1;
      int i = first_index; 
      HugeInt adder = result;
      while(i <= last_index)
      {
         // Simply Add to the place in question, multiply by the
         // divisor, and compare to the numerator.
         while((result * right) <= *this)
         {
           result += adder;
         } 
         if(i != last_index)
         {
            // Just surpassed the value, decrement
            result -= adder;
            // Change our adder to be 10x less
            adder >>= 1;
         }
         else
         {
            // Last index, make sure we don't have to subtract one
            if(result * right > *this)
            {
               result -= adder;
            }
         }
         ++i;
      }
   }
   return result;
}

// Division
HugeInt HugeInt::operator / (const uint64_t& right) const
{
   return *this / HugeInt(right);
}

// Division-Assign
HugeInt& HugeInt::operator /= (const HugeInt& right)
{
   *this = *this / right;
   return *this;
}

// Division-Assign
HugeInt& HugeInt::operator /= (const uint64_t& right)
{
   *this = *this / HugeInt(right);
   return *this;
}

// String cast operator
HugeInt::operator string() const
{
   // String to be built
   string s;
   // Calculate the offset to start with
   int offset = DEFAULT_SIZE - size();
   for(int i = offset; i < DEFAULT_SIZE; i++)
   {
      // Just append the ASCII value
      s += (char)((*this)[i] + 0x30);
   }
   return s;
}

// Size function
// Finds the number of used characters in the array
uint16_t HugeInt::size() const
{
   // We know the last number must be filled in.
   int i = DEFAULT_SIZE - 2;
   // Iterate backwards until we find a zero
   while(i > 0 && (*this)[i] != 255)
   {
      i--;
   }
   // Whether we reached index 0 or stopped early,
   // still return the distance we travelled
   return DEFAULT_SIZE - i - 1;
}
