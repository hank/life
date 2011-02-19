/* LED Blink with a watchdog timer.
 */
#ifndef F_CPU
    // A reasonable default clock speed
    #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "basic_functions.h"

ISR(WDT_vect)
{
        TOGGLE(PORTB, PB2);
}

int main()
{
    // Turn on LED output pin
    SET_HIGH(DDRB, PB2);

    // Set timer prescale to 101 (F/1024)
    WDTCR |= _BV(WDP2) | _BV(WDP0);

    // Set timer to count with F_CPU
    SET_HIGH(WDTCR, WDIE);

    // Enable overflow interrupt
    SET_HIGH(TIMSK, TOIE0);

    // Turn on interrupts!
    sei();

    for(;;);
    return 0;
}
