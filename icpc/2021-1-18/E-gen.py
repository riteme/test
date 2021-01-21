from random import *

n = 10**5

print(n, 1)
print(*[randint(0, 1) for i in range(n)])
