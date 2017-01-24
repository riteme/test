import sys
from random import *

n = int(sys.argv[1])
t = int(sys.argv[2])
m = n * (n - 1) / 2

def gen(size, delta):
    for u in range(0, n):
        for v in range(u + 1, n):
            print u + delta, v + delta

print n * t, m * t
for i in range(0, t):
    gen(n, n * i)
