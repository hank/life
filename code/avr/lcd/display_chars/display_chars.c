/* Nametag for HD44780 LCDs
   This is a fun little app that prints some 3x3 bouncing text and
   some custom messages underneath it that rotate.
*/
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"
#define CHAR_3X3_TYPE
#include "chars.h"

// Puts 3x3 characters in CGRAM slot `slot`
// x1 and x2 must be in progmem.
void construct_3x3s_P(uint8_t slot, const unsigned char * x1, 
                                    const unsigned char * x2)
{
    char tmp[8] = {0};
    memcpy_P(tmp, x1, 3);
    memcpy_P(&tmp[4], x2, 3);
    lcd_custom_char(slot, tmp);
}

// 16 characters only!
static const char s1[17] PROGMEM =  "github.com/hank";
static const char s2[17] PROGMEM =  "   ralree.com";
static const char s3[17] PROGMEM =  " Experienced in";
static const char s4[17] PROGMEM =  " C C++ Ruby PHP";
static const char s5[17] PROGMEM =  "    Learning";
static const char s6[17] PROGMEM =  "  AVR/Embedded";
static const char s7[17] PROGMEM =  "Camping.goes :)";
static const char s8[17] PROGMEM =  " ::OSCON 2011::";
static const char s9[17] PROGMEM =  "Oregon Brewfest!";
static const char s10[17] PROGMEM = "Make this thing";
static const char s11[17] PROGMEM = "  bit.ly/lcdnt";

static const char * s_array[] = {
    s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11
};

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES);
    lcd_clrscr();

    construct_3x3s_P(0, _char_3x3_e,     _char_3x3_g);
    construct_3x3s_P(1, _char_3x3_r,     _char_3x3_r);
    construct_3x3s_P(2, _char_3x3_i,     _char_3x3_e);
    construct_3x3s_P(3, _char_3x3_k,     _char_3x3_g);
    construct_3x3s_P(4, _char_3x3_space, _char_3x3_g);
    lcd_puts_len("\0\1\2\3\4\5\6\7", 8);

    // Screws everything up after next refresh because
    // CGRAM has been overwritten.
    // construct_3x3s_P(0, _char_3x3_q, _char_3x3_r);
    // construct_3x3s_P(1, _char_3x3_s, _char_3x3_t);
    // construct_3x3s_P(2, _char_3x3_u, _char_3x3_v);
    // construct_3x3s_P(3, _char_3x3_w, _char_3x3_x);
    // construct_3x3s_P(4, _char_3x3_y, _char_3x3_z);
    // construct_3x3s_P(5, _char_3x3_1, _char_3x3_2);
    // construct_3x3s_P(6, _char_3x3_3, _char_3x3_4);
    // construct_3x3s_P(7, _char_3x3_5, _char_3x3_6);
    // lcd_puts_len("\0\1\2\3\4\5\6\7", 8);
    
    // Move the text back and forth.
    int i = 0, j = 0;
    int dir = 1;
    int xy = 0;
    for(;;)
    {
        lcd_clrscr();
        // Move first line around
        if(dir == -1 && i == 0) {dir *= -1;}
        else if(dir == 1 && i >= 11) {dir *= -1;}
        
        lcd_gotoxy(i, 0);
        lcd_puts_len("\0\1\2\3\4", 5);

        // Display messages
        xy = lcd_getxy();
        lcd_gotoxy(0, 1);
        if(j == (sizeof(s_array) / 2)) j = 0;
        lcd_puts_p(s_array[j%(sizeof(s_array) / 2)]);
        ++j;
        lcd_gotoxy(xy>>4, xy&0x0F);
        i+=dir;
        _delay_ms(2500);
    }
    return 0;
}
