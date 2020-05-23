from random import *

n = 50000
CMAX = 2*10**5

print(n, n)
for i in range(n):
    op = randint(1, 2)
    if op == 1:
        m = randint(1, CMAX)
        v = randint(1, CMAX)
        print(1, m, 1, v)
    else:
        r = randint(1, n)
        print(2, r)

print(0, 0)