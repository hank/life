/* CTC (Clear on Timer Compare) LED Blink.
 */
#ifndef F_CPU
    // A reasonable default clock speed
    #warning No F_CPU Defined, using 8Mhz
    #define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/sleep.h>

#include <util/delay.h>

#include <stdio.h>

#include "basic_functions.h"

/*
 * This demonstrate how to use the avr_mcu_section.h file
 * The macro adds a section to the ELF file with useful
 * information for the simulator
 */
//#include "avr_mcu_section.h"
//AVR_MCU(F_CPU, "attiny85");


//const struct avr_mmcu_vcd_trace_t _mytrace[]  _MMCU_ = {
//    { AVR_MCU_VCD_SYMBOL("DDRB"), .what = (void*)&DDRB, },
//    { AVR_MCU_VCD_SYMBOL("TCCR0B"), .what = (void*)&TCCR0B, },
//    { AVR_MCU_VCD_SYMBOL("TCCR0A"), .what = (void*)&TCCR0A, },
//    { AVR_MCU_VCD_SYMBOL("TCNT0"), .what = (void*)&TCNT0, },
//    { AVR_MCU_VCD_SYMBOL("OCR0A"), .what = (void*)&OCR0A, },
//};

int main()
{
    // Enable external OC0A
    SET_HIGH(DDRB, PB0);

    // Set toggle of OC0A on compare match
    SET_HIGH(TCCR0A, COM0A0);

    // Set timer to count with F_CPU
    SET_HIGH(TCCR0B, CS10);
    SET_HIGH(TCCR0B, CS11);

    // Set timer prescale
    SET_HIGH(TCCR0B, CS01);

    // Turn on CTC
    SET_HIGH(TCCR0A, WGM01);
    OCR0A = 254;

    for(;;) 
    {
        if(OCF0A) 
        {
            SET_LOW(PORTB, PB0); 
            _delay_ms(1000);
        }
    }

    return 0;
}
