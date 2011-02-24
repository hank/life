#include <avr/io.h>
#include "lcd.h"

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);
    for(;;);
}
