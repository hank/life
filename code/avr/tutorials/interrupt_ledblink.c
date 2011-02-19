/* LED Blink with interrupts.
 */
#ifndef F_CPU
    // A reasonable default clock speed
    #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "basic_functions.h"

volatile int timer_overflow_count = 0;

ISR(TIM0_OVF_vect)
{
    if(++timer_overflow_count > 5)
    {
        TOGGLE(PORTB, PB2);
        timer_overflow_count = 0;
    }
}

int main()
{
    // Turn on LED output pin
    SET_HIGH(DDRB, PB2);

    // Set timer prescale to 101 (F/1024)
    TCCR0B |= _BV(CS00) | _BV(CS02);

    // Set timer to count with F_CPU
    SET_HIGH(TCCR0B, CS10);

    // Enable overflow interrupt
    SET_HIGH(TIMSK, TOIE0);

    // Turn on interrupts!
    sei();

    for(;;);
    return 0;
}
