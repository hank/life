#!/bin/bash
sudo avrdude -c usbtiny -p t85 -e -U flash:w:${1}
