// floor.cpp
#include "floor.h"
void Floor::boardPassengers(Elevator& elevator)
{
   uint8_t i = 0;
   uint8_t max_passengers = elevator.getMaxPassengers();
   while(i < max_passengers)
   {
      // Add the front
      elevator.addPassenger(getPassengers().front()); 
      // Remove the front
      getPassengers().pop_front();
      ++i;
   }
   // All aboard.
}

bool Floor::hasPassengersGoingUp()
{
   bool status = false;
   std::list<Passenger>::const_iterator iter = 
      getPassengers().begin();
   while(iter != getPassengers().end())
   {
      if(iter->getStartFloor() < iter->getEndFloor())
      {
         status = true;
         break;
      }
   }
   return status;
}

bool Floor::hasPassengersGoingDown()
{
   bool status = false;
   std::list<Passenger>::const_iterator iter = 
      getPassengers().begin();
   while(iter != getPassengers().end())
   {
      if(iter->getStartFloor() > iter->getEndFloor())
      {
         status = true;
         break;
      }
   }
   return status;
}
