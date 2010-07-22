#ifndef Elevator_H
#define Elevator_H

#include <list>
#include <boost/cstdint.hpp>

#include "passenger.h"

class Elevator
{
   public:
      Elevator()
      : state(STOPPED)
      , state_counter(0)
      , floor_number(1)
      {}

      // getPassengers: gets the passengers list
      std::list<Passenger>& getPassengers()
      {
         return this->passengers;
      }

      // addPassenger: adds a passenger to the elevator
      void addPassenger(const Passenger& passenger)
      {
         getPassengers().push_back(passenger);
      }

      uint8_t getMaxPassengers()
      {
         return this->max_passengers;
      }

      uint16_t getDestinationFloor()
      {
         return this->destination_floor;
      }

      void setDestinationFloor(uint16_t destination_floor)
      {
         this->destination_floor = destination_floor;
      }

      // Main state machine stepping function
      void step();

      enum MovementState
      {
         STOPPED,
         STOPPING,
         MOVING_UP,
         MOVING_DOWN
      };

   private:
      std::list<Passenger> passengers;
      MovementState state;
      // Used for tracking number of seconds in state
      uint8_t state_counter;
      // Current floor number
      uint16_t floor_number;
      uint16_t destination_floor;
      static const uint8_t max_passengers = 8;
};

#endif
