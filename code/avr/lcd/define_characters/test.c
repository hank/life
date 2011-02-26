#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

// Include the chars we want
#define CHAR_USE_OPEN_RECTANGLE
#define CHAR_USE_HEART
#include "chars.h"

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES );
    lcd_clrscr();

    // Testing if x,y are set wrong
    lcd_gotoxy(3, 1);

    // Load character
    lcd_custom_char_p(0x00, _char_open_rectangle);
    lcd_custom_char_p(0x01, _char_heart);

    // We better still be at 3, 1
    lcd_putc(0);
    lcd_putc(1);
    lcd_putc(255);

    for(;;);
}
