# AVR XBM toy

## What is this?
This is an interesting little toy that shows what can be done with the
HD44780-compatible display and an AVR chip.

## Requirements
I'm using an ATtiny2313 for this project, and that's what's set up in the
Makefile.  Basically, the XBM format is an ASCII C source code file that
contains a static array of a bitmap.  You can include this file in a C program
and easily print it out to the screen.  I wanted to print it out on my LCD.  

You also need a compiled copy of [LCDiesel](https://github.com/hank/lcdiesel/).

## Usage
First, make an XBM file in GIMP (80x16 pixels, Black and White).  Then, run
`make xbm`, which will convert it to an AVR memory-friendly file, overwriting
the original but saving a backup to a .bak file.  Have a look at
`xbm_display.c`.  It contains a `#include` statement for the xbm.  Change that
to point to yours.  Make sure the stuff in the Makefile makes sense for your
tools (MCU, programmer).  Then, type `make` and `make install`.

## Pitfalls
You can only display 8 custom characters at any time on the LCD.  Every time
it refreshes, it re-reads all the characters from CGRAM, so if any of them
have changed, it clobbers characters you've already displayed.  It would sure
be nice if this was a setting in the LCD controller that could be overridden.
Therefore, this code will only fill 1/4 of the screen with an 80x16 XBM file.
I know no way around this.

## Final Notes
This was a good learning experience.  I found out that my 2313 has a
*very* small amount of RAM (128 Bytes).  I was trying to keep the entire XBM
in there, which didn't work at all.  A bigger MCU would have fared better.  By
keeping it in program space, my problems were solved.  That's why the `make
xbm` task exists.
