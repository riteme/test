N=8
B=3
intervals=[(1,3),(7,8),(3,4)]

def length_of(interval):
    return interval[1] - interval[0] + 1

def begin_of(interval):
    i, j = interval
    return i

def end_of(interval):
    i, j = interval
    return j

f = []
for i in range(0, N + 1):
    f.append(0)

for i in range(1, N + 1):
    for interval in intervals:
        s = begin_of(interval)
        e = end_of(interval)
        length = length_of(interval)

        if e == i:
            f[e] = max(f[e], f[s - 1] + length)

    f[i] = max(f[i - 1], f[i])

print(f[N])
