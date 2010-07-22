#ifndef Passenger_H
#define Passenger_H
#include <fstream>
#include <boost/cstdint.hpp>

class Passenger
{
   public:

      Passenger(const uint16_t& time,
         const uint16_t& start_floor,
         const uint16_t& end_floor
      )
      : time(time)
      , start_floor(start_floor)
      , end_floor(end_floor)
      {}

      uint16_t getStartFloor() const
      {
         return this->start_floor;
      }
      uint16_t getEndFloor() const
      {
         return this->start_floor;
      }
      uint16_t getTime() const
      {
         return this->time;
      }
      
   private:
      uint16_t time;
      uint16_t start_floor; 
      uint16_t end_floor; 
};

std::ostream& operator<< (std::ostream& stream, const Passenger& passenger);

#endif
