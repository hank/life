#!/usr/bin/python
from Xlib import X, display
d = display.Display()
s = d.screen()
a = 1
b = 1
while True:
   root = s.root
   root.warp_pointer(100+(a+1)%2,100+(b+1)%2)
   a += 1
   b += 1
   d.sync()
