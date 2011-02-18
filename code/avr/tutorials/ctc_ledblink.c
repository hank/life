/* CTC (Clear on Timer Compare) LED Blink.
 */
#ifndef F_CPU
    // A reasonable default clock speed
    #warning No F_CPU Defined, using 8Mhz
    #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "basic_functions.h"

int main()
{
    // Enable external OC0A
    SET_HIGH(DDRB, DDB0);

    // Set timer to count with F_CPU
    SET_HIGH(TCCR0B, CS10);

    // Turn on CTC
    SET_WGM_85(TCCR0, 0, 1, 0);
    OCR0A = 50;

    // Set toggle of OC0A on compare match
    SET_HIGH(TCCR0A, COM0A0);
    SET_HIGH(TCCR0A, COM0A1);

    // Set timer prescale to 101 (F/1024)
    TCCR0B |= _BV(CS02) | _BV(CS00);

    // Loop Forever
    for(;;);

    return 0;
}
