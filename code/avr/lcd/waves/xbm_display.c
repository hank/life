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

//    xbm_set_char(omg_bits, 0);
    char data[8];
    uint16_t offset = 0;
    unsigned char * xbm = omg_bits;
    // XBM files are in reverse bit order.  Lower bit is first bit.
    uint8_t i;
    //for(i=0; i<8; ++i) {
    //    data[i] = bit_reverse(xbm[offset+(i*10)]) >> 3;
    //}
    //lcd_custom_char(0, data);

    data[0] = bit_reverse(xbm[offset+0]) >> 3;
    data[1] = bit_reverse(xbm[offset+10]) >> 3;
    data[2] = bit_reverse(xbm[offset+20]) >> 3;
    data[3] = bit_reverse(xbm[offset+30]) >> 3;
    data[4] = bit_reverse(xbm[offset+40]) >> 3;
    data[5] = bit_reverse(xbm[offset+50]) >> 3;
    data[6] = bit_reverse(xbm[offset+60]) >> 3;
    data[7] = bit_reverse(xbm[offset+70]) >> 3;
    lcd_custom_char(0, data);

    data[0] = (bit_reverse(xbm[offset+0])&7) <<2 | (bit_reverse(xbm[offset+1])>>6);
    data[1] = (bit_reverse(xbm[offset+10])&7)<<2 | (bit_reverse(xbm[offset+11])>>6);
    data[2] = (bit_reverse(xbm[offset+20])&7)<<2 | (bit_reverse(xbm[offset+21])>>6);
    data[3] = (bit_reverse(xbm[offset+30])&7)<<2 | (bit_reverse(xbm[offset+31])>>6);
    data[4] = (bit_reverse(xbm[offset+40])&7)<<2 | (bit_reverse(xbm[offset+41])>>6);
    data[5] = (bit_reverse(xbm[offset+50])&7)<<2 | (bit_reverse(xbm[offset+51])>>6);
    data[6] = (bit_reverse(xbm[offset+60])&7)<<2 | (bit_reverse(xbm[offset+61])>>6);
    data[7] = (bit_reverse(xbm[offset+70])&7)<<2 | (bit_reverse(xbm[offset+71])>>6);
    lcd_custom_char(1, data);

    data[0] = bit_reverse(xbm[offset+1]) >>1 &31;
    data[1] = bit_reverse(xbm[offset+11])>>1 &31;
    data[2] = bit_reverse(xbm[offset+21])>>1 &31;
    data[3] = bit_reverse(xbm[offset+31])>>1 &31;
    data[4] = bit_reverse(xbm[offset+41])>>1 &31;
    data[5] = bit_reverse(xbm[offset+51])>>1 &31;
    data[6] = bit_reverse(xbm[offset+61])>>1 &31;
    data[7] = bit_reverse(xbm[offset+71])>>1 &31;
    lcd_custom_char(2, data);

    data[0] = (bit_reverse(xbm[offset+1])&1)<<4  | (bit_reverse(xbm[offset+2])>>4);
    data[1] = (bit_reverse(xbm[offset+11])&1)<<4 | (bit_reverse(xbm[offset+12])>>4);
    data[2] = (bit_reverse(xbm[offset+21])&1)<<4 | (bit_reverse(xbm[offset+22])>>4);
    data[3] = (bit_reverse(xbm[offset+31])&1)<<4 | (bit_reverse(xbm[offset+32])>>4);
    data[4] = (bit_reverse(xbm[offset+41])&1)<<4 | (bit_reverse(xbm[offset+42])>>4);
    data[5] = (bit_reverse(xbm[offset+51])&1)<<4 | (bit_reverse(xbm[offset+52])>>4);
    data[6] = (bit_reverse(xbm[offset+61])&1)<<4 | (bit_reverse(xbm[offset+62])>>4);
    data[7] = (bit_reverse(xbm[offset+71])&1)<<4 | (bit_reverse(xbm[offset+72])>>4);
    lcd_custom_char(3, data);

    data[0] = ((bit_reverse(xbm[offset+2]))<<1&30)  | (bit_reverse(xbm[offset+3])>>7);
    data[1] = ((bit_reverse(xbm[offset+12]))<<1&30) | (bit_reverse(xbm[offset+13])>>7);
    data[2] = ((bit_reverse(xbm[offset+22]))<<1&30) | (bit_reverse(xbm[offset+23])>>7);
    data[3] = ((bit_reverse(xbm[offset+32]))<<1&30) | (bit_reverse(xbm[offset+33])>>7);
    data[4] = ((bit_reverse(xbm[offset+42]))<<1&30) | (bit_reverse(xbm[offset+43])>>7);
    data[5] = ((bit_reverse(xbm[offset+52]))<<1&30) | (bit_reverse(xbm[offset+53])>>7);
    data[6] = ((bit_reverse(xbm[offset+62]))<<1&30) | (bit_reverse(xbm[offset+63])>>7);
    data[7] = ((bit_reverse(xbm[offset+72]))<<1&30) | (bit_reverse(xbm[offset+73])>>7);
    lcd_custom_char(4, data);

    data[0] = ((bit_reverse(xbm[offset+3]))>>2&31);
    data[1] = ((bit_reverse(xbm[offset+13]))>>2&31);
    data[2] = ((bit_reverse(xbm[offset+23]))>>2&31);
    data[3] = ((bit_reverse(xbm[offset+33]))>>2&31);
    data[4] = ((bit_reverse(xbm[offset+43]))>>2&31);
    data[5] = ((bit_reverse(xbm[offset+53]))>>2&31);
    data[6] = ((bit_reverse(xbm[offset+63]))>>2&31);
    data[7] = ((bit_reverse(xbm[offset+73]))>>2&31);
    lcd_custom_char(5, data);

    data[0] = ((bit_reverse(xbm[offset+3])&3)<<3)  | (bit_reverse(xbm[offset+4])>>5);
    data[1] = ((bit_reverse(xbm[offset+13])&3)<<3) | (bit_reverse(xbm[offset+14])>>5);
    data[2] = ((bit_reverse(xbm[offset+23])&3)<<3) | (bit_reverse(xbm[offset+24])>>5);
    data[3] = ((bit_reverse(xbm[offset+33])&3)<<3) | (bit_reverse(xbm[offset+34])>>5);
    data[4] = ((bit_reverse(xbm[offset+43])&3)<<3) | (bit_reverse(xbm[offset+44])>>5);
    data[5] = ((bit_reverse(xbm[offset+53])&3)<<3) | (bit_reverse(xbm[offset+54])>>5);
    data[6] = ((bit_reverse(xbm[offset+63])&3)<<3) | (bit_reverse(xbm[offset+64])>>5);
    data[7] = ((bit_reverse(xbm[offset+73])&3)<<3) | (bit_reverse(xbm[offset+74])>>5);
    lcd_custom_char(6, data);

    data[0] = bit_reverse(xbm[offset+4])&31;
    data[1] = bit_reverse(xbm[offset+14])&31;
    data[2] = bit_reverse(xbm[offset+24])&31;
    data[3] = bit_reverse(xbm[offset+34])&31;
    data[4] = bit_reverse(xbm[offset+44])&31;
    data[5] = bit_reverse(xbm[offset+54])&31;
    data[6] = bit_reverse(xbm[offset+64])&31;
    data[7] = bit_reverse(xbm[offset+74])&31;
    lcd_custom_char(7, data);

    lcd_putc(0);
    lcd_putc(1);
    lcd_putc(2);
    lcd_putc(3);
    lcd_putc(4);
    lcd_putc(5);
    lcd_putc(6);
    lcd_putc(7);
    
    for(;;);
    //{
    //    lcd_command(LCD_MOVE_DISP_RIGHT);
    //    _delay_ms(50);
    //}
    return 0;
}
