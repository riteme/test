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

        P = [0] + map(int, s.split())

        cnt = 0
        for i in xrange(1, len(P)):
            if i == P[i]:
                cnt += 1
        # marked = [False] * len(P)
        # for i in xrange(1, len(P)):
        #     if not marked[i]:
        #         cnt += 1
        #         x = i
        #         while not marked[x]:
        #             marked[x] = True
        #             x = P[x]

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
