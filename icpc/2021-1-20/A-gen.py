from random import *

n = 10**5
q = 10**5
P = 30
C = 10**9

print(n, P)
print(*[randint(0, C) for i in range(n)])
print(q)
for i in range(q):
    t = randint(1, 5)
    l = randint(1, n)
    r = randint(l, n)
    k = randint(0, C)
    print(t, l, r, k)
