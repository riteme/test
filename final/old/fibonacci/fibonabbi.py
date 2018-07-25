#!/usr/bin/env python
#
# Copyright 2015 riteme
#

# Fibonacci series:
a, b = 0, 1

bMax = int(input('Enter the max value of number: '))
while b < bMax:
    print(b, end = ', ')
    a, b = b, a + b

