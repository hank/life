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

    // Load character
    lcd_custom_char_p(0x00, c_1);

    uint8_t i = 0;
    //lcd_command(_BV(LCD_CGRAM));  /* set CG RAM start address 0 */
    //for (; i<8; ++i) {
    //    lcd_data(pgm_read_byte_near(&c_1[i]));
    //}
    //lcd_gotoxy(0,1);

    for(i=0;;++i)
    {
        i % 2 == 0 ? lcd_putc(0) : lcd_putc(255);
    }
}
