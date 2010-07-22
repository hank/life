// elevator.cpp
#include <iostream>
using std::cout;
using std::endl;
#include "elevator.h"
#include "passenger.h"
#include "building.h"

void Elevator::letPassengersOff()
{
   std::list<Passenger>::iterator iter = this->getPassengers().begin();
   std::list<Passenger>::iterator to_erase = iter;
   Building* building = Building::getInstance();
   bool erase_passenger = false;
   while(iter != this->getPassengers().end())
   {
      if(iter->getEndFloor() == this->floor_number)
      {
         // Passenger's ride is over.
         cout << "Passenger " << *iter 
            << " has reached destination" << endl;
         erase_passenger = true;
         to_erase = iter;
      }
      else
      {
         cout << "Passenger " << *iter 
            << " isn't ready yet: " << 
               static_cast<unsigned int>(iter->getEndFloor()) << endl;
      }
      ++iter;
      if(erase_passenger)
      {
         cout << "Wait time: " 
              << static_cast<unsigned int>(building->getTicker() - to_erase->getTime()) 
              << endl;
         // Keep a running sum and count of wait times in building
         building->addWaitTime(to_erase->getTravelStart() - to_erase->getTime());
         // Also keep travel times
         building->addTravelTime(building->getTicker() - to_erase->getTravelStart());
         getPassengers().erase(to_erase);
         erase_passenger = false;
         building->decrementPassengerNumber();
      }
   }
}
void Elevator::collectPassengers()
{
   Building* building = Building::getInstance();
   Floor& floor = building->getFloor(this->floor_number);
   if( (this->destination_floors.front() < this->floor_number &&
            floor.hasPassengersGoingDown()) ||
         (this->destination_floors.front() > this->floor_number && 
          floor.hasPassengersGoingUp())
     )
   {
      std::list<Passenger>::iterator iter = 
         floor.getPassengers().begin();
      std::list<Passenger>::iterator to_erase = iter; 
      bool erase_passenger = false;
      while(iter != floor.getPassengers().end())
      {
         // Make sure we have room
         if(this->getPassengers().size() == getMaxPassengers())
         {
            // We can't take any more.
            // Continue moving
            break;
         }
         if( (this->destination_floors.front() < this->floor_number && 
                  iter->getEndFloor() < this->floor_number) ||
               (this->destination_floors.front() > this->floor_number && 
                iter->getEndFloor() > this->floor_number)
           )
         {
            // Pick them up!
            cout << "Boarding Passenger " << *iter << endl;
            // Set the travel time
            Building* building = Building::getInstance();
            addDestinationFloor(iter->getEndFloor());
            iter->setTravelStart(building->getTicker());
            this->getPassengers().push_back(*iter);
            to_erase = iter;
            erase_passenger = true;
         }
         ++iter;
         if(erase_passenger)
         {
            floor.getPassengers().erase(to_erase);
            erase_passenger = false;
         }
      }
   }
}

bool Elevator::reachedDestination()
{
   bool val = false;
   std::list<uint16_t>::iterator iter = getDestinationFloors().begin();
   while(iter != getDestinationFloors().end())
   { 
      if(this->floor_number == *iter)
      {
         val = true;
         break;
      }
      ++iter;
   }
   return val;
}

void Elevator::removeDestination(const uint16_t& floor_number)
{
   std::list<uint16_t>::iterator iter = getDestinationFloors().begin();
   std::list<uint16_t>::iterator to_remove = iter;
   bool remove_dest = false;
   while(iter != getDestinationFloors().end())
   { 
      if(this->floor_number == *iter)
      {
         to_remove = iter;
         remove_dest = true;
      }
      ++iter;
      if(remove_dest)
      {
         remove_dest = false;
         getDestinationFloors().erase(to_remove);
      }
   }
}

void Elevator::step()
{
   // Main state machine functionality
   // If we're in a stopped state
   if(this->state == STOPPED)
   {
      // First, check if we have a destination floor
      if(!this->destination_floors.empty())
      {
         // Have we reached a destination?
         if(reachedDestination())
         {
            // Brilliant.  Let's let people out.
            letPassengersOff();
            this->state_counter = 0;
            // Remove this destination
            removeDestination(this->floor_number);
            // If we have another destination, start up again
            if(!this->destination_floors.empty())
            {
               startMovement();
            }
         }
         else
         {
            // OK - we're not there yet.  
            // See if we need to pick anyone up
            collectPassengers();
            // Since we're not there yet, change to a moving state
            this->state_counter = 0;
            if(this->destination_floors.front() < this->floor_number)
            {
               this->state = MOVING_DOWN;
               --this->floor_number;
            }
            else if(this->destination_floors.front() > this->floor_number)
            {
               this->state = MOVING_UP;
               ++this->floor_number;
            }
            
         }
      }
      else
      {
         // No more destination floors
         // Just idle.
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
      // Check if we're at our destination floor
      if(this->floor_number == this->destination_floors.front())
      {
         // We're here.  Start the stop state.
            this->state_counter = 0;
            this->state = STOPPING;
      }
      else
      {
         // Check if current floor has waiting passengers
         Building* building = Building::getInstance();
         Floor& floor = building->getFloor(this->floor_number);
         if((getPassengers().size() != getMaxPassengers()) &&
            (
            (this->state == MOVING_DOWN && floor.hasPassengersGoingDown()) ||
            (this->state == MOVING_UP   && floor.hasPassengersGoingUp())
            )
           )
         {
            // Begin stopping process if we're not full
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
               cout << "Moving ";
               this->state_counter = 0;
               if(this->state == MOVING_DOWN)
               {
                  --this->floor_number;
                  cout << "Down";
               }
               else
               {
                  ++this->floor_number;
                  cout << "Up";
               }
               cout << " to floor " 
                    << static_cast<unsigned int>(this->floor_number)
                    << " (destination: "
                    << static_cast<unsigned int>(this->destination_floors.front())
                    << "), Passengers: " 
                    << getPassengers().size()
                    << endl;
            }
         }
      }
   }
}

