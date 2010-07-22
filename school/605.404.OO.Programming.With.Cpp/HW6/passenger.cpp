#include "passenger.h"
Passenger::~Passenger()
{ 
   cout << "Goodbye " << *this << endl;
}
std::ostream& operator<< (std::ostream& stream, const Passenger& passenger)
{
   stream << passenger.getTime() << ": "
      << passenger.getStartFloor() << ", "
      << passenger.getEndFloor();
   return stream;
}
