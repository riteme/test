#!/usr/bin/env python3

from sys import *
from random import *

n = int(argv[1])
S = argv[2]

print(n)
print(' '.join(map(str, [randint(1, i) for i in range(1, n)])))
print(''.join(choice(S) for i in range(n)))
