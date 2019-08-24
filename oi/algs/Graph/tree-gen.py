#!/usr/bin/env pypy

import sys
from random import *

assert len(sys.argv) > 1

N = int(sys.argv[1])
S = [i for i in range(1, N + 1)]
shuffle(S)

print(N)
for i in range(1, N):
    father = choice(S[:i])

    print("{} {}".format(father, S[i]))
