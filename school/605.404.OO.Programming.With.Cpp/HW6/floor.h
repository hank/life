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

      // addPassenger: adds a passenger to the floor
      void addPassenger(const Passenger& passenger)
      {
         cout << "Adding Passenger " << passenger << endl;
         getPassengers().push_back(passenger);
      }

      bool hasPassengersGoingUp();
      bool hasPassengersGoingDown();

   private:
      uint8_t number;
      std::list<Passenger> passengers;
};

#endif
