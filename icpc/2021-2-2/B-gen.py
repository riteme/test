from random import *

n = 150000
C = 10**9
print(3, n)
for i in range(3):
    print(*[randint(1, C) for j in range(n)])