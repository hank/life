// building.h
// Contains Building class
#ifndef Building_H
#define Building_H

#include <vector>
#include <boost/array.hpp>
#include <boost/cstdint.hpp>

#include "elevator.h"
#include "passenger.h"
#include "floor.h"

// Building class 
// A singleton that contains the floors and elevators in a building.  Serves
// as a link for the elevators and floors to query and communicate passenger
// information.
class Building
{
   public:

      // Singleton instance function
      static Building* getInstance()
      {
         static Building * building = new Building;
         return building;
      }

      // Mutable getFloor
      // Returns a floor with a give identifier
      Floor& getFloor(uint8_t number)
      {
         return this->floors[number];
      }

      // Mutable getElevator
      // Returns an elevator with a give identifier
      Elevator& getElevator(uint8_t number)
      {
         return this->elevators[number];
      }

      // Tells the first free elevator (or a random one) about a new passenger
      // on a given floor
      void alertElevators(uint16_t floor_number);

      // setElevators sends each elevator through one time step (1 second)
      void stepElevators();
 
      // Returns whether all elevators are idle.
      // Means they have an empty list of destination floors and are not moving
      bool elevatorsIdle();

      // Returns a mutable reference to the building's clock/ticker
      uint64_t& getTicker()
      {
         return this->ticker;
      }

      // Adds a new passenger wait time to the global totals
      void addWaitTime(const uint64_t& wait_time)
      {
         this->wait_total += wait_time;
         ++this->wait_count;
      }

      // Adds a new passenger travel time to the global totals
      void addTravelTime(const uint64_t& travel_time)
      {
         this->travel_total += travel_time;
         ++this->travel_count;
      }

      // Calculates and returns the average wait time for all passengers
      double averageWaitTime()
      {
         return static_cast<double>(this->wait_total) / this->wait_count;
      }

      // Calculates and returns the average total time for all passengers
      double averageTravelTime()
      {
         return static_cast<double>(this->travel_total) / this->travel_count;
      }

      // Keeps track of the number of passengers in the building
      // who are riding or waiting
      uint16_t getPassengerNumber()
      {
         return this->passenger_number;
      }

      // Increments the global number of passengers
      void incrementPassengerNumber()
      {
         ++this->passenger_number;
      }

      // Decrements the global number of passengers
      void decrementPassengerNumber()
      {
         --this->passenger_number;
      }

   private:

      // Private Default Constructor
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

      // Private Copy Constructor
      Building(const Building& b)
      {}

      // Storage for 100 floors
      Floor floors[100];
      // Storage for 4 floors
      Elevator elevators[4];

      uint16_t passenger_number;
      uint64_t ticker;

      uint64_t wait_total;
      uint16_t wait_count;
      uint64_t travel_total;
      uint16_t travel_count;
};

#endif
