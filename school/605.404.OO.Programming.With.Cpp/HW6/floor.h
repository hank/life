// floor.h
// Contains the Floor class
#ifndef Floor_H
#define Floor_H

#include <list>
#include <boost/cstdint.hpp>
#include "passenger.h"

// Floor
// Facilitates a floor in a building that contains passengers
// Meant to interact with Elevators, but not dependent
// Only depends on Passenger class
class Floor
{
   public:
      // Default constructor
      // NOTE: User needs to assign a floor after initialization
      // Used for arrays of Floors
      Floor()
      {}

      // Single-param constructor
      // Must take a number for the floor
      Floor(const uint8_t number)
      : number(number)
      {}

      // Gets a mutable list of passengers
      std::list<Passenger>& getPassengers()
      {
         return this->passengers;
      }

      // Returns the floor number
      uint8_t getNumber()
      {
         return this->number;
      }

      // Sets the floor number
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

      // Whether we have passengers who want to go up
      bool hasPassengersGoingUp();
      // Whether we have passengers who want to go down
      bool hasPassengersGoingDown();

   private:
      uint8_t number;
      std::list<Passenger> passengers;
};

#endif
