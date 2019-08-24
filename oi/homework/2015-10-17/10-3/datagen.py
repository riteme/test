import random

N = 100
RANDOMRANGE = 450

print(N)

L = []
for i in range(0, N + 1):
    L.append(str(random.randrange(0, RANDOMRANGE + 1)))

print(" ".join(L))
