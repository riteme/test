#!/usr/bin/pypy

import sys

p = int(sys.argv[1])
print "p =", p
for x in xrange(1, p):
    E = set()
    L = []
    t = 1
    while True:
        if t in E:
            break
        E.add(t)
        L.append(t)
        t = t * x % p
    E = [str(v) if v != t else '[' + str(v) for v in L]
    print ("[%2d] %2d: " % (len(L), x)) + ' → '.join(E) + ']'
    print '\t ⇒ {' + ', '.join(map(str, sorted(L))) + '}'


