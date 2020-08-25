n = 10**5
q = n

from random import *

W = 10**4
print(n, q)
print(' '.join(str(randint(1, W)) for i in range(n)))
for v in range(2, n + 1):
    u = randint(1, v - 1)
    print(u, v)
for _ in range(q):
    op = choice('?!')
    x = randint(1, n)
    v = randint(1, 10**9)
