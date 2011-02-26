/* Defines custom characters.  To use, just #define CHAR_USE_x where x is the
 * name of the desired character in all caps.  Then access it in your program
 * with _char_x where x is the lowercase name.
 * 
 * The reason these are not enabled by default is to keep program size down.
 */
#ifndef CHARS_H
#define CHARS_H

#ifdef CHAR_USE_HEART
static const PROGMEM unsigned char _char_heart[] = {0x00, 0x1B, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};
#endif

#ifdef CHAR_USE_OPEN_RECTANGLE
static const PROGMEM unsigned char _char_open_rectangle[] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F};
#endif

#endif // CHARS_H
