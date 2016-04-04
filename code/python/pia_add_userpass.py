#!/usr/bin/env python
import fileinput
import re
from glob import glob
for line in fileinput.input(inplace=1, backup='.bak'):
    line = re.sub('auth-user-pass\s*$', 'auth-user-pass PIA.txt', line.rstrip())
    print(line)
