#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

static const PROGMEM unsigned char c_1[] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES );
    lcd_clrscr();

    // Testing if x,y are set wrong
    lcd_gotoxy(3, 1);

    // Load character
    lcd_custom_char_p(0x00, c_1);

    // We better still be at 3, 1
    lcd_putc(0);
    lcd_putc(255);

    for(;;);
}
