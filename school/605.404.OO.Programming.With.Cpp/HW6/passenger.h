#ifndef Passenger_h
#define Passenger_h

#include <boost/cstdint.hpp>

class Passenger
{
   public:
      // Default constructor
      // Initializes destination floor
      Passenger(const uint16_t& time,
                const uint8_t& start_floor,
                const uint8_t& end_floor)
      : time(time)
      , start_floor(start_floor)
      , end_floor(end_floor)
      {}

      uint16_t getTime() const
      {
         return this->time;
      }

      uint16_t getStartFloor() const
      {
         return this->start_floor;
      }

      uint16_t getEndFloor() const
      {
         return this->end_floor;
      }

   private:
      uint16_t time;
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
