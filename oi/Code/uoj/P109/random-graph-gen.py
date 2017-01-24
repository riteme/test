from random import *

n = 71
m = 1501

print n, m
E = set()
while len(E) < m:
    u = randrange(0, n - 1)
    v = randrange(u + 1, n)
    E.add("%s %s" % (u, v))

print "\n".join(list(E))
