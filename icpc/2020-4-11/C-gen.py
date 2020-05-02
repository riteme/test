#!/usr/bin/python3

from random import *

n = 10**5
C = 10**8

print(n, n * (n - 1) // 4)
for i in range(n):
    print(randint(-C, C), randint(-C, C))