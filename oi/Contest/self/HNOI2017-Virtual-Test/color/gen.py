#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 4:
    print "Usage: %s [N] [Q] [C]" % sys.argv[0]
    exit(-1)

ALPHABET = [
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F'
]

for arg in sys.argv:
    if arg.startswith('-'):
        a, d = arg.split('-')
        ALPHABET = [d.upper()]

def random_char():
    global ALPHABET
    return choice(ALPHABET)

n = int(sys.argv[1])
q = int(sys.argv[2])
c = int(sys.argv[3])
print "".join([random_char() for i in range(0, n)])
print q

Q = [i + 1 for i in range(0, min(16, c))]
shuffle(Q)
for i in range(0, min(len(Q), q)):
    print Q[i]
for i in range(0, q - len(Q)):
    print randint(1, c)
