from random import *

n = 500
C = 700

S = set()
while len(S) < n:
    #x = randint(-C, C)
    x = randint(-1, 0)
    y = randint(-C, C)
    z = randint(0, 1)
    S.add((x, y, z))

print(n)
for x, y, z in S:
    #print(x, y, z, randint(1, 2))
    if x < 0:
        print(x, y, z, 1)
    else:
        print(x, y, z, 2)
