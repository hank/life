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
         return this->destination_floors.front();
      }

      std::list<uint16_t>& getDestinationFloors()
      {
         return this->destination_floors;
      }

      void addDestinationFloor(uint16_t destination_floor)
      {
         this->destination_floors.push_back(destination_floor);
      }

      // Start moving depending on destination
      void startMovement()
      {
         if(this->destination_floors.front() > this->floor_number)
         {
            this->state = MOVING_UP;
         }
         else if(this->destination_floors.front() < this->floor_number)
         {
            this->state = MOVING_DOWN;
         }
         this->state_counter = 0;
      }

      bool idle()
      {
         return getState() == STOPPED && getDestinationFloors().size() == 0;
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

      const MovementState getState()
      {
         return this->state;
      }

   private:
      void letPassengersOff();
      void collectPassengers();
      bool reachedDestination();
      void removeDestination(const uint16_t& floor_number);

      std::list<Passenger> passengers;
      MovementState state;
      // Used for tracking number of seconds in state
      uint8_t state_counter;
      // Current floor number
      uint16_t floor_number;
      std::list<uint16_t> destination_floors;
      static const uint8_t max_passengers = 8;
};

#endif
