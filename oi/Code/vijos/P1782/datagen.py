import random

NMAX = 1000000
MMAX = 1000000
DMAX = 1000000000

R = []
for i in range(0, NMAX):
    R.append(str(random.randrange(1, DMAX + 1)))

M = []
for i in range(0, MMAX):
    a = random.randrange(1, NMAX + 1)
    b = random.randrange(1, NMAX + 1)
    M.append(
        '{} {} {}'.format(random.randrange(1, DMAX + 1), min(a, b), max(a, b)))

print(NMAX, MMAX)
print(' '.join(R))
print('\n'.join(M))
