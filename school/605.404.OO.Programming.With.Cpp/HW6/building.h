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
      bool elevatorsIdle();

      static Building* getInstance()
      {
         static Building * building = new Building;
         return building;
      }

      uint64_t& getTicker()
      {
         return this->ticker;
      }

      void addWaitTime(const uint64_t& wait_time)
      {
         this->wait_total += wait_time;
         ++this->wait_count;
      }

      double averageWaitTime()
      {
         return static_cast<double>(this->wait_total) / this->wait_count;
      }

      // Keeps track of the number of passengers in the building
      // Who are riding or waiting
      uint16_t getPassengerNumber()
      {
         return this->passenger_number;
      }

      void incrementPassengerNumber()
      {
         ++this->passenger_number;
      }

      void decrementPassengerNumber()
      {
         --this->passenger_number;
      }

   private:

      // Single-param constructor
      // Must take a number for the floor
      Building()
      : ticker(0)
      , wait_total(0)
      , wait_count(0)
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

      uint16_t passenger_number;
      uint64_t ticker;

      uint64_t wait_total;
      uint16_t wait_count;
};

#endif
