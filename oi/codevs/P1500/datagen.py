#!/usr/bin/env pypy

from random import randint, choice, shuffle

N = 100000

print(N)
S = [chr(randint(ord('a'), ord('z'))) for i in range(0, N)]
print("".join(S))
