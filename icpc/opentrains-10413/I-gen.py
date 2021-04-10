from random import *

n, q = (4 * 10**5, ) * 2
op = []

while q > 0:
    m = 4
    q -= m
    mod = randint(2 * 10**8, 10**9)

    buf = [m, mod]
    for i in range(m):
        l = randint(1, n)
        s = randint(0, n - l)
        r = randint(l, l + s)
        buf += [l, r]

    op.append(' '.join(map(str, buf)))

S = "a" * 2000 + "b"
print(n, len(op))
# print(''.join(choice(S) for i in range(n)))
print('a' * (n - 1) + 'b')
print('\n'.join(op))