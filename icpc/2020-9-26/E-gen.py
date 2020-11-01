from random import *

n = 40000
m = 5
q = 40000
C = 10**6

print(n, m, q)

W = []
for i in range(m):
    l = randint(-C, C - 1)
    r = randint(l + 1, C)
    y = randint(1, C)
    W.append((l, r, y))

cnt = 0
while cnt < n:
    x = randint(-C, C)
    y = randint(1, C)
    ok = True
    for i in range(m):
        if y == W[i][2] and W[i][0] <= x <= W[i][1]:
            ok = False

    if ok:
        print(x, y)
        cnt += 1

for l, r, y in W:
    print(l, r, y)

for i in range(q):
    x = randint(-C, C)
    y = randint(1, C)
    print(x, -y)
