#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES );
    lcd_clrscr();
    char omg[] = "OMG";
    int j = 0;
    while(j < 3) { lcd_putc(omg[j]); j++; }
    for(;;);
    //    if(i == 0 || i > 0x7F) i = 0x20;
    //    if(i % 8 == 0) lcd_home();
    //    lcd_putc(i);
    //    _delay_ms(150);
    //    ++i;
    //}
}
