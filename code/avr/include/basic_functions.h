/* Basic AVR Functions 
   Makes writing code for the AVR more pleasant
*/

// Basic Bitwise Functions
#define SET_LOW(port, pin)  port &= ~_BV(pin)
#define SET_HIGH(port, pin) port |=  _BV(pin)
#define TOGGLE(port, pin)   port ^=  _BV(pin)
