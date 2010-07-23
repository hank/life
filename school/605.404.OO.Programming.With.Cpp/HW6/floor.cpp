// floor.cpp
// Inlcudes the Floor implementation
#include "floor.h"

// Checks if the floor has any passengers going up by iterating through the
// passenger list
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
      ++iter;
   }
   return status;
}

// Checks if the floor has any passengers going down by iterating through the
// passenger list
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
      ++iter;
   }
   return status;
}
