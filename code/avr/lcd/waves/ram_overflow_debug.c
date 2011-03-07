#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"
#include "omg.xbm"
#include "helpers.h"

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES);
    lcd_clrscr();

    unsigned char * xbm = omg_bits;
    // XBM files are in reverse bit order.  Lower bit is first bit.
    char data[8] = {0};
    uint8_t i;
    for(i=0; i<8; i++) {
        data[i] = bit_reverse(pgm_read_byte_near(&xbm[i*10])) >> 3;
    }
    //lcd_puts_numeric(data, 8);
    lcd_custom_char(0, data);

    //data[0] = bit_reverse(xbm[0]) >> 3;
    //data[1] = bit_reverse(xbm[10]) >> 3;
    //data[2] = bit_reverse(xbm[20]) >> 3;
    //data[3] = bit_reverse(xbm[30]) >> 3;
    //data[4] = bit_reverse(xbm[40]) >> 3;
    //data[5] = bit_reverse(xbm[50]) >> 3;
    //data[6] = bit_reverse(xbm[60]) >> 3;
    //data[7] = bit_reverse(xbm[70]) >> 3;
    //lcd_custom_char(0, data);

    lcd_putc(0);
    
    for(;;);
    return 0;
}
