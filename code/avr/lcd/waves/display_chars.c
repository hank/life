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
#define CHAR_3X3_TYPE
#include "chars.h"

// Puts 3x3 characters in CGRAM slot `slot`
// x1 and x2 must be in progmem.
void construct_3x3s_P(uint8_t slot, const unsigned char * x1, 
                                    const unsigned char * x2)
{
    uint8_t tmp[8] = {0};
    memcpy_P(tmp, x1, 3);
    memcpy_P(&tmp[4], x2, 3);
    lcd_custom_char(slot, tmp);
}

int main(void)
{
    /* initialize display, cursor off */
    lcd_init(LCD_DISP_ON);
    lcd_command(LCD_FUNCTION_4BIT_2LINES);
    lcd_clrscr();

    construct_3x3s_P(0, _char_3x3_a, _char_3x3_b);
    construct_3x3s_P(1, _char_3x3_c, _char_3x3_d);
    construct_3x3s_P(2, _char_3x3_e, _char_3x3_f);
    construct_3x3s_P(3, _char_3x3_g, _char_3x3_h);
    construct_3x3s_P(4, _char_3x3_i, _char_3x3_j);
    construct_3x3s_P(5, _char_3x3_k, _char_3x3_l);
    construct_3x3s_P(6, _char_3x3_m, _char_3x3_n);
    construct_3x3s_P(7, _char_3x3_o, _char_3x3_p);
    lcd_puts_len("\0\1\2\3\4\5\6\7\n", 9);

    construct_3x3s_P(0, _char_3x3_q, _char_3x3_r);
    construct_3x3s_P(1, _char_3x3_s, _char_3x3_t);
    construct_3x3s_P(2, _char_3x3_u, _char_3x3_v);
    construct_3x3s_P(3, _char_3x3_w, _char_3x3_x);
   // construct_3x3s_P(4, _char_3x3_y, _char_3x3_z);
   // construct_3x3s_P(5, _char_3x3_1, _char_3x3_2);
   // construct_3x3s_P(6, _char_3x3_3, _char_3x3_4);
   // construct_3x3s_P(7, _char_3x3_5, _char_3x3_6);
   // lcd_puts_len("\0\1\2\3\4\5\6\7", 8);
    
    for(;;);
    //{
    //    lcd_command(LCD_MOVE_DISP_RIGHT);
    //    _delay_ms(50);
    //}
    return 0;
}
