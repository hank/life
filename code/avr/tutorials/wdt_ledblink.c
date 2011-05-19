/* LED Blink with a watchdog timer.
 */
#include "basic_functions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

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

    // Use the Power Down sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    for(;;) sleep_mode();
    return 0;
}
