#ifndef Passenger_H
#define Passenger_H
#include <fstream>

class Passenger
{
   public:
      uint16_t getStartFloor()
      uint16_t getEndFloor()
      uint16_t getTime()
      
   private:
      uint16_t start_floor; 
      uint16_t end_floor; 
};

std::ostream& operator<< (std::ostream& stream, const Passenger& passenger)
{
   stream << passenger.getTime() << ": "
      << passenger.getStartFloor() << ", "
      << passenger.getEndFloor();
   return stream;
}

#endif
