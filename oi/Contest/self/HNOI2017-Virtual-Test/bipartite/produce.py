#!/usr/bin/env pypy

import sys
from os import system as sh

if len(sys.argv) < 6:
    print "Usage: %s [N] [Q] [T] [G] [ID]" % sys.argv[0]
    exit(-1)

n = sys.argv[1]
q = sys.argv[2]
t = sys.argv[3]
generator = sys.argv[4]
idx = sys.argv[5]

print "Generating origin data..."
sh("./gen-%s.py %s %s 0 > bipartite.in" % (generator, n, q))

print "Getting answer..."
sh("./a.out < bipartite.in > bipartite.out")

if t == '1':
    print "Encrypting..."
    sh("./encrypt.py bipartite.in bipartite.out > bipartite%s.in" % idx)
else:
    sh("cp bipartite.in bipartite%s.in" % idx)

sh("cp bipartite.out bipartite%s.ans" % idx)

print "Finished!"
