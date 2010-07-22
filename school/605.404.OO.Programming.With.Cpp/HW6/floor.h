#ifndef Floor_H
#define Floor_H

#include <list>
#include <boost/cstdint.hpp>

#include "elevator.h"

class Floor
{
   public:
      // Default constructor
      // Need to assign a floor after initialization
      // Used for arrays of Floors
      Floor()
      {}

      // Single-param constructor
      // Must take a number for the floor
      Floor(const uint8_t number)
      : number(number)
      {}

      std::list<Passenger>& getPassengers()
      {
         return this->passengers;
      }

      uint8_t getNumber()
      {
         return this->number;
      }

      void setNumber(const uint16_t& number)
      {
         this->number = number;
      }

      // Boards as many passengers as possible on the elevator
      // Modifies Elevator
      void boardPassengers(Elevator& elevator);

      // addPassenger: adds a passenger to the floor
      void addPassenger(const Passenger& passenger)
      {
         getPassengers().push_back(passenger);
      }

      bool hasPassengersGoingUp();
      bool hasPassengersGoingDown();

   private:
      uint8_t number;
      std::list<Passenger> passengers;
};

#endif
