// floor.cpp
#include "floor.h"
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
