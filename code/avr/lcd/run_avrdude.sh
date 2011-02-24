#!/bin/bash
sudo avrdude -c usbtiny -p t2313 -e -U flash:w:main.hex
