from random import randint

N = 10000000
M = 20000000

E = []
for i in range(0, M):
    E.append("{} {} {}".format(randint(1, N), randint(1, N), randint(1, 1000)))

print(N, M)
print("\n".join(E))
