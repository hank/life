// passenger.cpp
// Contains the Passenger implementation
#include "passenger.h"

// Destructor
// Prints a bit of information about the object before deletion
Passenger::~Passenger()
{ 
   cout << "Goodbye " << *this << endl;
}

// ostream operator for Passenger
// Allows printing a Passenger to a stream
std::ostream& operator<< (std::ostream& stream, const Passenger& passenger)
{
   stream << passenger.getTime() << ": "
      << passenger.getStartFloor() << ", "
      << passenger.getEndFloor();
   return stream;
}
