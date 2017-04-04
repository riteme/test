#!/usr/bin/env python

def readline():
    return [int(x) for x in raw_input().split()]

n, m = readline()
print "%.6f" % (n * (n - 1) / 2.0 / m)
