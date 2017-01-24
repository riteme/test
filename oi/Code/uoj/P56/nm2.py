n, _1, _2 = [int(x) for x in raw_input().split()]
dist = [int(x) for x in raw_input().split()]

WMAX = 20000

dist = list(enumerate(dist))
dist = sorted(dist, key=lambda x: x[1])
delta = 0
last = 1

print n, 2 * n - 1, 10
for i in range(2, n + 1):
    u = dist[i - 1][0] + 1
    d = dist[i - 1][1]

    if d - delta <= WMAX:
        print last, u, d - delta
    else:
        last = dist[i - 2][0] + 1
        delta = dist[i - 2][1]
        print last, u, d - delta

for i in range(0, n):
    print i + 1, i + 1, 0
