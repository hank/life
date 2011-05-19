/* LED Blink.
 */
#include "basic_functions.h"
#include <avr/io.h>
#include <util/delay.h>

int main()
{
    uint16_t elapsed = 0;
    // Turn on LED output pin
    SET_HIGH(DDRB, PB2);

    // Set timer to count with F_CPU
    SET_HIGH(TCCR0B, CS10);
    // Set timer prescale to 101 (F/1024)
    TCCR0B |= _BV(CS00) | _BV(CS02);
    for(;;)
    {
        if(TCNT0 == 254)
        {
            TCNT0 = 0;
            ++elapsed;
            if(elapsed % 10 == 0) TOGGLE(PORTB, PB2);
        }
    }
    return 0;
}
