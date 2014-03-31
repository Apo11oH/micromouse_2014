#!/usr/bin/env python

for i in range(0, 16*16):
    if ((i>0) and (i%16 == 0)): print()
    print("{:4d}".format(i), end="")
