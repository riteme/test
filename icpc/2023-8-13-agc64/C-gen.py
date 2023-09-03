import random

print(1)
n = 3
RMAX = 10**18
print(n)
# p = sorted(random.sample(list(range(0, RMAX)), 2 * n))
p = []
for i in range(2 * n):
    p.append(random.randint(0, RMAX))
p = sorted(p)
for i in range(0, 2 * n, 2):
    print(p[i], p[i + 1])
