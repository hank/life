#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES );
    lcd_clrscr();
    int i = 0;
    lcd_puts_P("   I love you\n");
    lcd_puts_P("     Kelsey");
    char c;
    for(;;++i)
    {
        if(i%2==0) c = 0xDF;
        else c = 0x20;
        lcd_gotoxy(0, 0);
        lcd_putc(c);
        lcd_gotoxy(0, 1);
        lcd_putc(c);
        lcd_gotoxy(15, 0);
        lcd_putc(c);
        lcd_gotoxy(15, 1);
        lcd_putc(c);
        _delay_ms(500);
    }
}
