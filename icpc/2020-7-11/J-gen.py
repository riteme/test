n = 100000
q = 100000
CMAX = 1000000000

from random import *

print(n, q)
print(' '.join(str(randint(1, CMAX)) for i in range(n)))
for i in range(q):
    l = randint(1, n)
    r = randint(l, n)
    print(l, r)