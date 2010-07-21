#ifndef Floor_H
#define Floor_H

#include <queue>
#include <boost/cstdint.hpp>

#include "passenger.h"
#include "elevator.h"

class Floor
{
   public:
      // Single-param constructor
      // Must take a number for the floor
      Floor(const uint8_t number)
      : number(number)
      {}

      std::queue<Passenger>& getPassengers()
      {
         return this->passengers;
      }

      uint8_t getNumber()
      {
         return this->number;
      }

      // Boards as many passengers as possible on the elevator
      // Modifies Elevator
      void boardPassengers(Elevator& elevator)
      {
         uint8_t i = 0;
         uint8_t max_passengers = elevator.getMaxPassengers();
         while(i < max_passengers)
         {
            // Add the front
            elevator.addPassenger(getPassengers().front()); 
            // Remove the front
            getPassengers().pop();
            ++i;
         }
         // All aboard.
      }

      // addPassenger: adds a passenger to the floor
      void addPassenger(const Passenger& passenger)
      {
         getPassengers().push(passenger);
      }

   private:
      uint8_t number;
      std::queue<Passenger> passengers;
};

#endif
