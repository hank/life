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
/*
// Takes an xbm array and cuts it into 5-bit custom characters for LCD
// display.  Loads the characters into CGRAM.
// xbm parameter MUST point to at least an 75-byte array!
// offset parameter is added to every array index into xbm
inline void xbm_set_char(uint8_t* xbm, uint16_t offset)
{
    char data[8];
    // XBM files are in reverse bit order.  Lower bit is first bit.
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
}
*/
#endif
