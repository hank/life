/* LED Pulsate with PWM
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "attiny85");

const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
    { AVR_MCU_VCD_SYMBOL("DDRB"), .what = (void*)&DDRB, },
    { AVR_MCU_VCD_SYMBOL("TCCR0B"), .what = (void*)&TCCR0B, },
    { AVR_MCU_VCD_SYMBOL("TCCR0A"), .what = (void*)&TCCR0A, },
    { AVR_MCU_VCD_SYMBOL("TCNT0"), .what = (void*)&TCNT0, },
    { AVR_MCU_VCD_SYMBOL("OCR0A"), .what = (void*)&OCR0A, },
};

volatile int tcnt = 0;

int main()
{
    // Turn on LED output pin
    DDRB   |= _BV(PB2);

    // Set timer prescale to 101 (F/1024)
    //TCCR0B |= _BV(CS00) | _BV(CS02);
    TCCR0B |= _BV(CS00);

    // Set on match, clear on TOP 
    TCCR0A |= _BV(COM0A1) | _BV(COM0A0);

    // Set timer to count with F_CPU
    TCCR0B |= _BV(CS10);

    // Use Phase correct PWM, OCRA TOP
    TCCR0A |= _BV(WGM00);
    TCCR0B |= _BV(WGM02);

    // Enable overflow interrupt
    TIMSK  |= _BV(TOIE0);

    OCR0A = 0x80;
    //TCNT0 = 0;

    sei();

    uint16_t count = 10;
    uint8_t i;
    for(;;) 
    {
        tcnt = TCNT0;
        i = tcnt;
        if(--count == 0) cli();
        sleep_cpu();
    }
    return 0;
}
