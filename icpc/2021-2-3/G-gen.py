from random import *

n = 1000
C = 10**18

print(n)
print(*[randint(10**17, C) for i in range(n)])