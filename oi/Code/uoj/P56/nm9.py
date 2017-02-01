n, k, m = [int(x) for x in raw_input().split()]

data = [0] + [int(x) for x in raw_input().split()]
marked = [False] * (n + 1)

print n, m, k
for u in range(1, n + 1):
    marked[data[u]] = True
    for v in range(1, n + 1):
        if v >= data[u] or marked[v]:
            print u, v, 0
