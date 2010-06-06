#include <string>
using std::string;
#include <locale>
using std::isdigit;
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
#include <stdint.h>
class HugeInt
{
  public:
    // Default constructor - set a zero
    HugeInt()
    {
      // Create with default size
      this->integerFieldSize = 50;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Set to 255 (denotes empty)
      memset(this->integerField, 255, this->integerFieldSize - 1);
      // Set last value to 0
      this->integerField[this->integerFieldSize] = 0;
    }

    // 1 or 2 parameter constructor
    // Default size is 50
    HugeInt(int i, int size = 50)
    {
      this->integerFieldSize = size;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Set to 255 (denotes empty)
      memset(this->integerField, 255, this->integerFieldSize);
      // Set last value to 0
      this->integerField[this->integerFieldSize - 1] = 0;
      init(i);
    }

    // 1 or 2 parameter constructor
    // Default size is 50
    HugeInt(string s)
    {
      // XXX: Throw exception if s.length() > size
      this->integerFieldSize = s.size() + 1;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Set to 255 (denotes empty)
      memset(this->integerField, 255, this->integerFieldSize);
      // Set last value to 0
      this->integerField[this->integerFieldSize - 1] = 0;
      init(s);
    }

    // Copy constructor
    HugeInt(const HugeInt& from)
    {
      // Create space for new data
      integerFieldSize = from.integerFieldSize;
      integerField = new uint8_t[integerFieldSize];
      // Copy other data
      memcpy(integerField, from.integerField, integerFieldSize);
    }

    // Initialize the instance with a string
    // Expects a clean instance!
    void init(string s)
    {
      // Fill in integerField
      int offset = this->integerFieldSize - s.length();
      for(int j = 0; j < s.length(); j++)
      {
        // Add the characters
        if(isdigit(s[j]))
        {
          // Fill in with non-ASCII value of numeral
          this->integerField[offset + j] = s[j] - 0x30;
        }
        // XXX: else throw exception
      }
    }

    // Initialize the instance with an integer
    // Expects a clean instance!
    void init(int i)
    {
      // Disallow negative numbers
      if(i < 0) i = i * -1;
      // Fill in integerField
      int j = this->integerFieldSize - 1;
      while(i > 0 && j > 0)
      {
        // Take last base-10 digit
        this->integerField[j] = i % 10;
        // Remove last base-10 digit
        i /= 10;
        // Move back
        j--;
      }
    }

    // HugeInt equality operator
    bool operator == (const HugeInt& right) const
    {
      return true;
    }

    // HugeInt string equality operator
    bool operator == (const string& right) const
    {
      return true;
    }

    // Integer assignment operator
    HugeInt operator = (const int& right) 
    {
      // Groom space for new data
      memset(this->integerField, 255, this->integerFieldSize);
      // Initialize
      init(right);
      return *this;
    }

    // Integer addition
    HugeInt operator + (const int& right) 
    {
      return *this + HugeInt(right);
    }

    // HugeInt addition
    HugeInt operator + (const HugeInt& right) 
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
      for(int i = 1; i <= to_add->size(); i++)
      {
        result = to_add->integerField[to_add->integerFieldSize - i];
        result += dest.integerField[dest.integerFieldSize - i];
        if(result > 9) 
        {
          // Check for overflow
          if(i + 1 == dest.integerFieldSize)
          {
            // XXX: Exception
            return HugeInt(0);
          }
          else
          {
            // Set previous value to 1 if it's uninitialized.
            if(255 == dest.integerField[dest.integerFieldSize - i - 1])
            {
              dest.integerField[dest.integerFieldSize - i - 1] = 1;
            }
            else
            {
              // Increment previous digit
              dest.integerField[dest.integerFieldSize - i - 1]++;
            }
          }
        }
        dest.integerField[dest.integerFieldSize - i] = result % 10;
      }
      return dest;
    }

    // HugeInt subtraction
    HugeInt operator - (const HugeInt& right) 
    {
      HugeInt to_return = HugeInt(*this);
      // From the end of the integers, add and carry
      int8_t result;
      for(int i = 1; i < right.size() + 1; i++)
      {
        result = to_return.integerField[to_return.integerFieldSize - i];
        result -= right.integerField[right.integerFieldSize - i];
        if(result < 0) 
        {
          // Decrement previous value
          // If uninitialized, we've gone negative.
          if(255 == to_return.integerField[to_return.integerFieldSize - i - 1])
          {
            return HugeInt(0);
          }
          else
          {
            // Loop until we decrement something
            int j;
            for(j = to_return.integerFieldSize - i - 1;
                j > 0; j--)
            {
              // If we hit 255, we've underflowed
              if(to_return.integerField[j] == 255)
              {
                return HugeInt(0);
              }
              // If we hit a 0, just change to a 9 and keep iterating
              if(to_return.integerField[j] == 0)
              {
                to_return.integerField[j] = 9;
              }
              else
              {
                // Otherwise, just decrement and break.
                --to_return.integerField[j];
                break;
              }
            }
            // Make sure we haven't depleted the array
            if(0 == j)
            {
                return HugeInt(0);
            }
            result += 10;
          }
        }
        to_return.integerField[to_return.integerFieldSize - i] = result % 10;
      }
      return to_return;
    }

    // String cast operator
    operator string()
    {
      // String to be built
      string s;
      // Calculate the offset to start with
      int offset = this->integerFieldSize - size();
      for(int i = offset; i < this->integerFieldSize; i++)
      {
        // Just append the ASCII value
        s += (char)(this->integerField[i] + 0x30);
      }
      return s;
    }

    int size() const
    {
      // We know the last number must be filled in.
      int i = this->integerFieldSize - 2;
      // Iterate backwards until we find a zero
      while(i > 0 && this->integerField[i] != 255)
      {
        i--;
      }
      // Whether we reached index 0 or stopped early,
      // still return the distance we travelled
      return this->integerFieldSize - i - 1;
    }

  private:
    // Constant size
    uint32_t integerFieldSize;
    // Decimal Representation
    uint8_t * integerField;
};
