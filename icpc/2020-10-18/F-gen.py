from random import *

n = 99998
m = 100000
CMAX = 99

print(n, m)

for i in range(2, n + 1):
	u = randint(1, i - 1)
	print(1, u, i, randint(1, CMAX))

for i in range(m - n):
	print(0, randint(1, n), randint(1, n), randint(1, CMAX))
