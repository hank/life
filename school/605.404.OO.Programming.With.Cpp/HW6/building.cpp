// BOOST Random headers
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

// Other RNG stuff
#include <sys/time.h>

#include "building.h"

void Building::alertElevators(uint16_t floor_number)
{
   bool finished = false;
   for(uint16_t i = 0; i < 4; ++i)
   {
      Elevator& elevator = getElevator(i);
      // First, find any elevator that has no destination
      if(elevator.getDestinationFloors().empty())
      {
         elevator.addDestinationFloor(floor_number);
         elevator.startMovement();
         finished = true;
      }
   }
   if(!finished)
   {
      // We couldn't find an elevator that was free.  Just append
      // the floor to any elevator.
      struct timeval tv;
      gettimeofday(&tv, NULL);
      boost::mt19937 gen(tv.tv_usec);
      boost::uniform_int<> dist(0, 3);
      boost::variate_generator<boost::mt19937&,
         boost::uniform_int<> > roll(gen, dist);
      Elevator& elevator = getElevator(roll());
      elevator.addDestinationFloor(floor_number);
   }
}

void Building::stepElevators()
{
   for(uint16_t i = 0; i < 4; ++i)
   {
      getElevator(i).step();
   }
}

bool Building::elevatorsIdle()
{
   bool val = true;
   for(uint16_t i = 0; i < 4; ++i)
   {
      if(!getElevator(i).idle())
      {
         val = false;
         break;
      }
   }
   return val;
}
