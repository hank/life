# LCDiesel
This is just a little library on top of Peter Fleury's LCD library for the AVR
microcontroller series.  
## Compatibility
It should work for just about any AVR out there, but one needs to tweak the
header file in include with the pin settings.  The part you should care about
looks like this:

    #define LCD_PORT         PORTB        /**< port for the LCD lines     */
    #define LCD_DATA0_PORT   LCD_PORT     /**< port for 4bit data bit 0   */
    #define LCD_DATA1_PORT   LCD_PORT     /**< port for 4bit data bit 1   */
    #define LCD_DATA2_PORT   LCD_PORT     /**< port for 4bit data bit 2   */
    #define LCD_DATA3_PORT   LCD_PORT     /**< port for 4bit data bit 3   */
    #define LCD_DATA0_PIN    4            /**< pin for 4bit data bit 0    */
    #define LCD_DATA1_PIN    5            /**< pin for 4bit data bit 1    */
    #define LCD_DATA2_PIN    6            /**< pin for 4bit data bit 2    */
    #define LCD_DATA3_PIN    7            /**< pin for 4bit data bit 3    */
    #define LCD_CG_PORT      PORTB        /**< port for the LCD CG load   */
    #define LCD_CG0_PIN      0            /**< pin for 5bit CGRAM load 0  */
    #define LCD_CG1_PIN      1            /**< pin for 5bit CGRAM load 1  */
    #define LCD_CG2_PIN      2            /**< pin for 5bit CGRAM load 2  */
    #define LCD_CG3_PIN      3            /**< pin for 5bit CGRAM load 3  */
    #define LCD_CG4_PIN      4            /**< pin for 5bit CGRAM load 4  */
    #define LCD_RS_PORT      PORTD        /**< port for RS line           */
    #define LCD_RS_PIN       4            /**< pin  for RS line           */
    #define LCD_RW_PORT      LCD_RS_PORT  /**< port for RW line           */
    #define LCD_RW_PIN       5            /**< pin  for RW line           */
    #define LCD_E_PORT       LCD_RS_PORT  /**< port for Enable line       */
    #define LCD_E_PIN        6            /**< pin  for Enable line       */

These settings are what I'm currently using on my breadboard, and if you line
up the side of an ATTiny2313 with the +5V pin with pin 15 of the lcd (+5V for
Backlight), these settings should work for you too.  Otherwise, modify as
necessary.

## Requirements
* avr-gcc
* avr-objcopy
* make

## Building
The library and examples should build if you just type `make`.

## Usage
### Main LCD library
To use the library, just run `avr-gcc` like so:
	avr-gcc -o myprogram myprogram.c lcdiesel/lib/lcd.o
You'll need to add whatever `CFLAGS` you want to that command (like optimizations).

### Running Examples
    cd examples
    make flash_test_1

See `examples/Makefile` for other flashing.

## Advanced
### Custom Characters
Most HD44780-compatible LCDs have CGRAM, or Character Generation RAM that can
store a limited number of custom characters (usually 8).  There is a library
of custom characters for your perusal/customization in `include/chars.h`.
Each one is loadable in your program by doing a simple `#define` and
`#include`:
    #define CHAR_USE_OPEN_RECTANGLE
    #include "chars.h"

You can load them using this library like so:

    // Load character
    lcd_custom_char_p(0x00, _char_open_rectangle);

See `include/chars.h` for more details.
