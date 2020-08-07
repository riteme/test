from random import *

print(1)
n = 100000
print(n, n - 1)
for i in range(2, n + 1):
    j = randint(1, i - 1)
    print(i, j)