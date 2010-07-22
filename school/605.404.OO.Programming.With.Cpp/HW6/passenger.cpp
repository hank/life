#include "passenger.h"
std::ostream& operator<< (std::ostream& stream, const Passenger& passenger)
{
   stream << passenger.getTime() << ": "
      << passenger.getStartFloor() << ", "
      << passenger.getEndFloor();
   return stream;
}
