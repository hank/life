/* LED Pulsate with PWM
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

//#include "avr_mcu_section.h"
//AVR_MCU(F_CPU, "attiny85");
//
//const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
//    { AVR_MCU_VCD_SYMBOL("DDRB"), .what = (void*)&DDRB, },
//    { AVR_MCU_VCD_SYMBOL("TCCR0B"), .what = (void*)&TCCR0B, },
//    { AVR_MCU_VCD_SYMBOL("TCCR0A"), .what = (void*)&TCCR0A, },
//    { AVR_MCU_VCD_SYMBOL("TCNT0"), .what = (void*)&TCNT0, },
//    { AVR_MCU_VCD_SYMBOL("TIMSK"), .what = (void*)&TIMSK, },
//    { AVR_MCU_VCD_SYMBOL("OCR0A"), .what = (void*)&OCR0A, },
//};
//
//ISR(TIMER0_COMPA_vect)      // handler for Output Compare 2 overflow interrupt
//{
//    // this really doesn't no anything but proves a way to wake the main()
//    // from sleep at regular intervals
//    PORTB ^= 1;
//}
//
//volatile int tcnt = 0;

int main()
{
    // Turn on LED output pin
    DDRB   |= _BV(DDB0);

    // Toggle on match
    //TCCR0A |= _BV(COM0A0);
    TCCR0A |= _BV(COM0A1);

    // Set timer to count with F_CPU / 8
    TCCR0B |= _BV(CS10);
    TCCR0B |= _BV(CS01) | _BV(CS00);

    // Use Fast PWM, OCRA TOP
    TCCR0A |= _BV(WGM00);
    TCCR0A |= _BV(WGM01);
    //TCCR0B |= _BV(WGM02);
    OCR0A = 0x00;

    uint8_t dir = 1;
    uint16_t div = 500;
    uint16_t stall = 0;
    uint16_t stall_time = 500;
    for(;;) {
        // We only want to update every div counts
        if(TCNT0 % div != 0) continue;
        // Stall at the top and bottom, and change direction
        if(OCR0A == 255 || OCR0A == 0) {
            // Switch directon at top
            if(OCR0A == 255) dir = -1;
            else 
            {   // Disable LED at bottom
                // And switch direction
                DDRB  &= ~(_BV(DDB0));
                dir = 1; 
            }
            while(stall < stall_time) 
            { 
                ++stall;
                _delay_ms(10); 
            }
            // Turn output back on if necessary
            if(OCR0A == 0) DDRB  |= _BV(DDB0);
            stall = 0;
        }
        // General case - increment direction either way
        OCR0A += dir;
    }
    return 0;
}
