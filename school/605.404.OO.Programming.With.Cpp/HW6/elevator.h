#ifndef Elevator_H
#define Elevator_H

#include <queue>
#include <boost/cstdint.hpp>

#include "floor.h"

class Elevator
{
   public:
      Elevator()
      : state(STOPPED)
      , state_counter(0)
      , direction(NONE)
      {}

      // getPassengers: gets the passengers list
      std::queue<Passenger>& getPassengers()
      {
         return this->passengers;
      }

      // addPassenger: adds a passenger to the elevator
      void addPassenger(const Passenger& passenger)
      {
         getPassengers().push(passenger);
      }

      uint8_t getMaxPassengers()
      {
         return this->max_passengers;
      }


      enum MovementDirection
      {
         NONE,
         UP,
         DOWN
      }; 

      enum MovementState
      {
         STOPPED,
         STOPPING,
         MOVING_UP,
         MOVING_DOWN
      };

   private:
      std::queue<Passenger> passengers;
      MovementState state;
      uint8_t state_counter;
      MovementDirection direction;
      static const uint8_t max_passengers = 8;
};

#endif
