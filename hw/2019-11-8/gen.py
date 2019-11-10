#!/usr/bin/python3

from sys import *
from random import *

n = int(argv[1])
print(n)
L = [str(randint(1, 10**9)) for i in range(n)]
print(" ".join(L))
