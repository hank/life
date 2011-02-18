/* LED Blink.
 */
#ifndef F_CPU
    // A reasonable default clock speed
    #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define SET_LOW(port, pin)  port &= ~_BV(pin)
#define SET_HIGH(port, pin) port |=  _BV(pin)

void sleep(uint8_t millisec)
{
    while(millisec--) _delay_ms(1);
}

int main()
{
    SET_HIGH(DDRB, PB2);
    while(1)
    {
        SET_LOW(PORTB, PB2);
        sleep(1000);

        SET_HIGH(PORTB, PB2);
        sleep(1000);
    }
    return 0;
}
