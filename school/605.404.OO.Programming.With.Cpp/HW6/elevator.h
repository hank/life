// elevator.h
// Contains the Elevator class
#ifndef Elevator_H
#define Elevator_H

#include <list>
#include <boost/cstdint.hpp>

#include "passenger.h"

// Elevator
// A class to store an elevator and facilitate movement
// Moves between floors, picks up passengers on the way or at a destination,
// and drops them off at their EndFloor.  Has various limitations in movement
// for simulation.
class Elevator
{
   public:
      // Default Constructor
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

      // getMaxPassengers
      uint8_t getMaxPassengers()
      {
         return this->max_passengers;
      }

      // getDestinationFloors
      // Returns a mutable list of destination floors
      std::list<uint16_t>& getDestinationFloors()
      {
         return this->destination_floors;
      }

      // addDestinationFloor
      // Adds a given destination floor to our list
      void addDestinationFloor(uint16_t destination_floor)
      {
         this->destination_floors.push_back(destination_floor);
      }

      // startMovement
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

      // Checks if we're idle
      bool idle()
      {
         return getState() == STOPPED && getDestinationFloors().size() == 0;
      }


      // Main state machine stepping function
      void step();

      // Enumerable Movement State
      enum MovementState
      {
         STOPPED,
         STOPPING,
         MOVING_UP,
         MOVING_DOWN
      };

      // Returns the current Movement State
      const MovementState getState()
      {
         return this->state;
      }

   private:
      // Lets passengers off the elevator on the current floor
      void letPassengersOff();
      // Collects passengers from the current floor
      void collectPassengers();
      // Checks if we've reached a destination
      bool reachedDestination();
      // Removes a destination from our list
      void removeDestination(const uint16_t& floor_number);

      // STL list for passengers
      std::list<Passenger> passengers;
      // Current movement state
      MovementState state;
      // Used for tracking number of seconds in state
      uint8_t state_counter;
      // Current floor number
      uint16_t floor_number;
      // STL list for floors
      std::list<uint16_t> destination_floors;
      // All elevators only hold 8 passengers
      static const uint8_t max_passengers = 8;
};

#endif
