#!/usr/bin/env pypy

import sys

if len(sys.argv) < 3:
    print "Usage: %s [data.in] [data.out]" % sys.argv[0]
    exit(-1)

with open(sys.argv[1], "r") as reader:
    A, B, C = [int(x) for x in reader.readline().split()] 

S = set([A, B])
with open(sys.argv[2], "r") as reader:
    K = int(reader.readline())
    assert K <= 400, "K is limited to 400."

    for i in range(0, K):
        a, b = [int(x) for x in reader.readline().split()]
        assert a in S, "At #$s: Argument 'i' not created" % (i + 1)
        assert b in S, "At #%s: Argument 'j' not created" % (i + 1)
        assert a > b, "At #%s: j must less than i" % (i + 1)
        S.add(a - b)

assert C in S, "Incorrect solution"
print "OK!"
