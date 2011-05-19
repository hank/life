#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND

struct clock { 
    uint8_t second; 
    uint8_t minute; 
    uint8_t hour; 
};

void update_time(struct clock * c)
{
    lcd_home();
    lcd_putc(0x30 + (c->hour / 10));
    lcd_putc(0x30 + (c->hour % 10));
    lcd_putc(':');
    lcd_putc(0x30 + (c->minute / 10));
    lcd_putc(0x30 + (c->minute % 10));
    lcd_putc(':');
    lcd_putc(0x30 + (c->second / 10));
    lcd_putc(0x30 + (c->second % 10));
}

int main(void)
{
    struct clock c = {.second = 0, .minute = 0, .hour = 0};
    //struct clock c;
    //c.second = 0;
    //c.minute = 0;
    //c.hour = 0;
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES );
    lcd_clrscr();
    
    for(;;)
    {
        update_time(&c);
        _delay_ms(1000);
        c.second = (c.second + 1) % 60;
        if(c.second == 0) {
            c.minute = (c.minute + 1) % 60;
            if(c.minute == 0) c.hour = (c.hour + 1) % 24;
        }
    }
}
