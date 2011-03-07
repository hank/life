#ifndef XBM_HELPERS_H
#define XBM_HELPERS_H
// Reverses the order of bits in a byte. 
// I.e. MSB is swapped with LSB, etc. 
unsigned char bit_reverse(unsigned char x) 
{ 
    x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa); 
    x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc); 
    x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0); 
    return x;    
}
// Takes an xbm array and cuts it into 5-bit custom characters for LCD
// display.  Loads the characters into CGRAM.
// xbm parameter MUST point to at least an 75-byte array in PROGRAM MEMORY!
// offset parameter is added to every array index into xbm
inline void xbm_set_char(uint8_t* xbm, uint16_t offset)
{
    // XBM files are in reverse bit order.  Lower bit is first bit.
    char data[8];
    uint8_t i;
    for(i=0; i<8; i++) {
      data[i] = bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)])) >> 3;
    }
    lcd_custom_char(0, data);

    for(i=0; i<8; i++) {
      data[i] = (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)]))&7)<<2 |
                (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+1]))>>6);
    }
    lcd_custom_char(1, data);

    for(i=0; i<8; i++) {
      data[i] = bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+1]))>>1&31;
    }
    lcd_custom_char(2, data);

    for(i=0; i<8; i++) {
      data[i] = (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+1]))&1)<<4 |
                (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+2]))>>4);
    }
    lcd_custom_char(3, data);

    for(i=0; i<8; i++) {
      data[i] = ((bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+2])))<<1&30) |
                (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+3]))>>7);
    }
    lcd_custom_char(4, data);

    for(i=0; i<8; i++) {
      data[i] = bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+3]))>>2&31;
    }
    lcd_custom_char(5, data);

    for(i=0; i<8; i++) {
      data[i] = (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+3]))&3)<<3 |
                (bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+4]))>>5);
    }
    lcd_custom_char(6, data);

    for(i=0; i<8; i++) {
      data[i] = bit_reverse(pgm_read_byte_near(&xbm[offset+(i*10)+4]))&31;
    }
    lcd_custom_char(7, data);
}
#endif
