#!/usr/bin/env python
import time
import sys

transactions = eval(sys.stdin.read())
for t in transactions:
  print "\t".join((time.strftime("%Y/%m/%d %H:%M:%S", time.localtime(t['time'])), t['address'], str(t['amount'])))
