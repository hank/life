/* Basic AVR Functions 
   Makes writing code for the AVR more pleasant
*/

// Basic Bitwise Functions
#define SET_LOW(port, pin)  port &= ~_BV(pin)
#define SET_HIGH(port, pin) port |=  _BV(pin)
#define TOGGLE(port, pin)   port ^=  _BV(pin)

// Bits spread over 2 registers is annoying.
// NOTE: Only tested with Attiny85!
#define SET_WGM_85(reg, b1, b2, b3) \
  if(b1) SET_HIGH(reg##A, WGM02); \
  else SET_LOW(reg##A, WGM02); \
  if(b2) SET_HIGH(reg##B, WGM01); \
  else SET_LOW(reg##A, WGM01); \
  if(b3) SET_HIGH(reg##B, WGM00); \
  else SET_LOW(reg##A, WGM00);
