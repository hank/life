#include "building.h"
void Building::alertElevators(uint16_t floor_number)
{
   for(uint16_t i = 0; i < 4; ++i)
   {
      Elevator& elevator = getElevator(i);
      if(elevator.getDestinationFloor() == 0)
      {
         elevator.setDestinationFloor(floor_number);
      }
   }
}

void Building::stepElevators()
{
   for(uint16_t i = 0; i < 4; ++i)
   {
      getElevator(i).step();
   }
}
