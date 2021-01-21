#!/usr/bin/env python3

from random import *

n = 10**5
q = 10**5

print(n, q)
print('(' * (n // 2) + ')' * (n // 2))
for i in range(q):
	l = randint(1, n)
	r = randint(l, n)
	print(l, r)
