#ifndef Building_H
#define Building_H

#include <vector>
#include <boost/array.hpp>
#include <boost/cstdint.hpp>

#include "elevator.h"
#include "passenger.h"
#include "floor.h"

// Singleton!
class Building
{
   public:

      // Mutable getFloor
      Floor& getFloor(uint8_t number)
      {
         return this->floors[number];
      }

      Elevator& getElevator(uint8_t number)
      {
         return this->elevators[number];
      }

      void alertElevators(uint16_t floor_number);

      void stepElevators();

      static Building* getInstance()
      {
         static Building * building = new Building;
         return building;
      }

   private:

      // Single-param constructor
      // Must take a number for the floor
      Building()
      {
         for(uint16_t i = 0; i < 100; ++i)
         {
            uint16_t floor_number = i + 1;
            getFloor(i).setNumber(floor_number);
         }
      }

      // Copy Constructor
      Building(const Building& b)
      {}

      Floor floors[100];
      Elevator elevators[4];
};

#endif
