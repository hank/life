// passenger.h
// Contains the Passenger class
#ifndef Passenger_H
#define Passenger_H
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
#include <boost/cstdint.hpp>

// Forward declared for ostream operator declaration
class Passenger;

std::ostream& operator<< (std::ostream& stream, const Passenger& passenger);

// Passenger class
// Contains a passengers with a starting time, a beginning floor, and an ending
// floor.
// Passengers also have a travel start time to allow calculation of both
// travel and wait times.  
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

      ~Passenger();

      uint16_t getStartFloor() const
      {
         return this->start_floor;
      }
      uint16_t getEndFloor() const
      {
         return this->end_floor;
      }
      uint16_t getTime() const
      {
         return this->time;
      }

      uint16_t getTravelStart() const
      {
         return this->travel_start;
      }

      void setTravelStart(const uint16_t& travel_start)
      {
         this->travel_start = travel_start;
      }
      
   private:
      uint16_t time;
      uint16_t travel_start;
      uint16_t start_floor; 
      uint16_t end_floor; 
};

#endif
