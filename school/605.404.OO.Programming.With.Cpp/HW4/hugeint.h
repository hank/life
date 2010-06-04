#include <string>
using std::string;
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
      memset(this->integerField, 255, this->integerFieldSize);
    }

    // 1 or 2 parameter constructor
    // Default size is 50
    HugeInt(int i, int size = 50)
    {
      this->integerFieldSize = size;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Set to 255 (denotes empty)
      memset(this->integerField, 255, this->integerFieldSize);
      init(i);
    }

    // Copy constructor
    HugeInt(HugeInt& other)
    {
      // Create space for new data
      this->integerFieldSize = other.integerFieldSize;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Copy other data
      memcpy(this->integerField, other.integerField, 
             this->integerFieldSize);
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

    // HugeInt assignment operator
    void operator = (const HugeInt& right) 
    {
      // Groom space for new data
      delete[] this->integerField;
      this->integerFieldSize = right.integerFieldSize;
      this->integerField = new uint8_t[this->integerFieldSize];
      // Copy the entire integer field
      memcpy(this->integerField, 
             right.integerField, this->integerFieldSize);
    }

    // Integer assignment operator
    void operator = (const int& right) 
    {
      // Groom space for new data
      memset(this->integerField, 255, this->integerFieldSize);
      // Initialize
      init(right);
    }

    // uint64_t cast operator
    operator uint64_t()
    {
      uint64_t integerValue = 0;
      int j = 0;
      int multiplier = 1;
      for(j = this->integerFieldSize; j > 0; j--)
      {
        integerValue += this->integerField[j] * multiplier * 10;
        multiplier *= 10;
      }
      return integerValue;
    }

    // String cast operator
    operator string()
    {
      // String to be built
      string s;
      // Calculate the offset to start with
      int offset = this->integerFieldSize - size() + 1;
      for(int i = offset; i < this->integerFieldSize; i++)
      {
        // Just append the ASCII value
        s += (char)(this->integerField[i] + 0x30);
      }
      return s;
    }

    int size()
    {
      int i = this->integerFieldSize;
      // Iterate backwards until we find a zero
      while(i > 0 && this->integerField[i] != 0)
      {
        i--;
      }
      // Whether we reached index 0 or stopped early,
      // still return the distance we travelled
      return this->integerFieldSize - i;
    }

  private:
    // Constant size
    uint32_t integerFieldSize;
    // Decimal Representation
    uint8_t * integerField;
};
