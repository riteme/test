from random import *

n = 10**6
T = 9
print(T)
for i in range(T):
    L = randint(1, 100)
    R = randint(L, n)
    print(n, L, R)
    s = [str(randint(-1, 1)) for j in range(n)]
    print(' '.join(s))
