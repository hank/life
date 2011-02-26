export CC=avr-gcc
export OBJCOPY=avr-objcopy
export OBJCOPYFLAGS=
export MCU=attiny2313
export DUDE_MCU=t2313
export F_CPU =4000000
export CFLAGS =-Os -I.. -DF_CPU=$(F_CPU) -mmcu=$(MCU)
export DUDE_FLAGS =-p $(DUDE_MCU)
