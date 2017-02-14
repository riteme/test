import sys
from random import *

n = int(sys.argv[1])

T = []
for i in range(2, n + 1):
    u = randrange(1, i)
    T.append((u, i))

S = set(T)
E = []
for u in range(1, n + 1):
    for v in range(u + 1, n + 1):
        if not (u, v) in S:
            E.append((u, v))

print n, len(E), n - 1
print "\n".join(["%s %s 1" % x for x in E])
print "\n".join(["%s %s" % x for x in T])
print "1 " * n
