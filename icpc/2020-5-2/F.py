#!/usr/bin/pypy

# n, k = 0, 0
uk = 0
x, y = 0, 0
p = [[0, 0] for i in range(70)]

def f(n, k):
    global p

    i = 1 if k == uk else 0
    if p[n][i]:
        return p[n][i]

    if n == 1:
        if k == 2:
            return 1
        if k == -2:
            return 3
        if k == 0:
            return 6
        return 0

    if k >= (1 << (n + 1)):
        return 0
    if -k >= (1 << (n + 1)):
        return 0

    if k >= (1 << n):
        p[n][i] = f(n - 1, k - (1 << n))
        return p[n][i]
    if -k >= (1 << n):
        p[n][i] = f(n - 1, k + (1 << n)) + (1 << (2 * n - 1)) * ((k + (1 << (n + 1))) / 2)
        return p[n][i]

    p[n][i] = 2 * f(n - 1, k) + max((1 << (n - 1)) - abs(k) / 2, 0) * (1 << (2 * n))
    if k < 0:
        p[n][i] += f(n - 1, k + (1 << n)) - (k / 2 * (1 << (2 * n - 1)))
    else:
        p[n][i] += f(n - 1, k - (1 << n))
    return p[n][i]

n, uk = map(int, raw_input().split())
print f(n, uk) if uk % 2 == 0 else 0