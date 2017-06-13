#!/usr/bin/env python

#
# Copyright 2017 riteme
#

from sys import argv, version
from os.path import *

if version[0] == '3':
    xrange = range

if len(argv) == 1 or "--help" in argv or "-h" in argv:
    print("Participate answer checker & grader.")
    print("Usage: %s [ID] [--no-limit] [--help/-h]" % argv[0])
    print("\t--no-limit: Ignore the attempt limit (Set the limit to 1,000,000,000).")
    print("\t--help / -h: Show this message.")
    exit(0)

def ASSERT(expr, message):
    if not expr:
        print(message)
        exit(-1)

idx = int(argv[1])

INPUT_FILE = "puzzle{}.in".format(idx)
OUTPUT_FILE = "puzzle{}.out".format(idx)

ASSERT(exists(INPUT_FILE), "'{}' not found.".format(INPUT_FILE))
ASSERT(exists(OUTPUT_FILE), "'{}' not found.".format(OUTPUT_FILE))

inp = open(INPUT_FILE)
out = open(OUTPUT_FILE)

T, n, m, LIMIT = map(int, inp.readline().split())

if "--no-limit" in argv:
    LIMIT = 10**9

DOWN = 1
RIGHT = 2

def read_graph():
    G = [[0] * (m + 1) for i in xrange(n + 1)]

    x = 0
    while x < n:
        line = inp.readline().strip()

        if len(line) == 0:
            continue

        x += 1
        for y in xrange(1, m + 1):
            if line[y - 1] == '$' and G[x - 1][y] != DOWN:
                G[x][y] = DOWN
            elif line[y - 1] == '#' and G[x][y - 1] != RIGHT:
                G[x][y] = RIGHT

    return G

last = read_graph()

def rotate(x, y, line):
    if x < n and last[x][y] == RIGHT and last[x + 1][y] == RIGHT:
        last[x][y] = last[x][y + 1] = DOWN
        last[x + 1][y] = 0
    elif y < m and last[x][y] == DOWN and last[x][y + 1] == DOWN:
        last[x][y] = last[x + 1][y] = RIGHT
        last[x][y + 1] = 0
    else:
        ASSERT(False, "Can't rotate at ({}, {}) (at line {}).".format(x, y, line))

score = line = 0
cnt = LIMIT
for i in xrange(1, T + 1):
    cur = read_graph()

    try:
        k = int(out.readline())
        line += 1
    except:
        ASSERT(False, "Can't read integer 'k' at gate {}.".format(i))

    reported = False
    for j in xrange(k):
        if cnt <= 0:
            print("No opportunities left.")
            reported = True
            break

        cnt -= 1

        try:
            x, y = map(int, out.readline().split())
            line += 1
        except:
            ASSERT(False, "Can't read integer 'x' and 'y' at gate {}.".format(i))

        rotate(x, y, line)

    if last != cur:
        print("Can't open the gate {}.".format(i))
        break

    score = i
    last = cur

    if cnt <= 0:
        if not reported:
            print("No opportunities left after gate {}.".format(i))
        break

print("Score: {}\nTried {} times.".format(score, LIMIT - cnt))
