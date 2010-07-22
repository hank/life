// elevator.cpp
#include <iostream>
using std::cout;
using std::endl;
#include "elevator.h"
#include "passenger.h"
#include "building.h"
void Elevator::step()
{
   // Main state machine functionality
   // If we're in a stopped state
   if(this->state == STOPPED)
   {
      // First, check if we have a destination floor
      if(this->destination_floor != 0)
      {
         // Have we reached it?
         if(this->destination_floor == this->floor_number)
         {
            // Brilliant.  Let's let people out.
            std::list<Passenger>::iterator iter = 
               this->getPassengers().begin();
            while(iter != this->getPassengers().end())
            {
               if(iter->getEndFloor() == this->floor_number)
               {
                  // Passenger's ride is over.
                  cout << "Passenger " << *iter 
                     << " has reached destination" << endl;
                  this->getPassengers().erase(iter);
               }
               ++iter;
            }
         }
         // OK - we're not there yet.  See if we need the current floor
         std::list<Passenger>::iterator iter = 
            this->getPassengers().begin();
         while(iter != this->getPassengers().end())
         {
            if(iter->getEndFloor() == this->floor_number)
            {
               // Passenger's ride is over.
               cout << "Passenger " << *iter 
                  << " has reached destination" << endl;
               this->getPassengers().erase(iter);
            }
            ++iter;
         }
      }
   }
   // Handle Stopping state
   else if(this->state == STOPPING)
   {
      // Only a couple cases here
      if(this->state_counter < 2)
      {
         // Not done stoppping yet
         ++this->state_counter;
      }
      else
      {
         this->state_counter = 0;
         this->state = STOPPED;
      }
   }
   else if(this->state == MOVING_UP ||
           this->state == MOVING_DOWN)
   {
      // Check if current floor has waiting passengers
      Building* building = Building::getInstance();
      Floor& floor = building->getFloor(this->floor_number);
      if((this->state == MOVING_DOWN && floor.hasPassengersGoingDown()) ||
         (this->state == MOVING_UP   && floor.hasPassengersGoingUp())
        )
      {
         // Begin stopping process
         this->state_counter = 0;
         this->state = STOPPING;
      }
      else
      {
         // Otherwise, just keep moving right along
         // Takes 10 seconds to move between floors.
         if(this->state_counter < 10)
         {
            ++this->state_counter;
         }
         else
         {
            this->state_counter = 0;
            if(this->state == MOVING_DOWN)
            {
               --this->floor_number;
            }
            else
            {
               ++this->floor_number;
            }
         }
      }
   }
}

