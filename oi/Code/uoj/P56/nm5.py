n, k, c = [int(x) for x in raw_input().split()]
data = [int(x) for x in raw_input().split()]
last = {}

print n, n, k
for u, idx in enumerate(data, start=1):
    if not idx in last:
        last[idx] = (u, u)
    else:
        tail, head = last[idx]
        print tail, u, 0
        last[idx] = (u, head)

for tail, head in last.values():
    print tail, head, 0
