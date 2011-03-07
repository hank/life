/* XBM file display for HD44780 displays
   This page explains the format: http://www.martinreddy.net/gfx/2d/XBM.txt
   Images MUST be 80x16 pixels for a 16x2 line display.
   Just calculate the number of bits your display has.
*/
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

    xbm_set_char(omg_bits, 0);
    lcd_putc(0);
    lcd_putc(1);
    lcd_putc(2);
    lcd_putc(3);
    lcd_putc(4);
    lcd_putc(5);
    lcd_putc(6);
    lcd_putc(7);
    
    for(;;);
    return 0;
}
