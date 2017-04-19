#!/usr/bin/env pypy

minv = 2**64
maxv = 0
alls = 0
n = 0

try:
    while True:
        s = raw_input()

        if s.strip() == "":
            exit()

        P = map(int, s.split())

        cnt = 0
        for i in xrange(len(P)):
            if P[i] == i + 1:
                cnt += 1

        alls += cnt
        n += 1
        maxv = max(maxv, cnt)
        minv = min(minv, cnt)
        print cnt
except EOFError:
    pass

print "===="
print "min = ", minv
print "max = ", maxv
print "all = ", alls
print "E   = ", alls / float(n)
