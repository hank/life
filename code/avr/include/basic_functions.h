/* Basic AVR Functions 
   Makes writing code for the AVR more pleasant
*/

#ifndef F_CPU
    // A reasonable default clock speed
    #warning Using the default 8Mhz clock
    #define F_CPU 8000000UL
#endif

// Basic Bitwise Functions
#define SET_LOW(port, pin)  port &= ~_BV(pin)
#define SET_HIGH(port, pin) port |=  _BV(pin)
#define TOGGLE(port, pin)   port ^=  _BV(pin)
