#!/usr/bin/env pypy

from sys import stdin
from copy import copy, deepcopy

# stdin = open("data.in", "r")
# def raw_input():
#     return stdin.readline()

T, n, m, LIMIT = map(int, raw_input().split())

DOWN = 1
RIGHT = 2

def read_graph():
    G = [[0] * m for i in xrange(n)]

    x = 0
    while x < n:
        line = raw_input().strip()

        if len(line) == 0:
            continue

        for y in xrange(m):
            if line[y] == '$' and (x == 0 or G[x - 1][y] != DOWN):
                G[x][y] = DOWN
            elif line[y] == '#' and (y == 0 or G[x][y - 1] != RIGHT):
                G[x][y] = RIGHT

        x += 1

    return G

op = None
D = []
R = []

def rotate(G, x, y):
    # print "rotate", x + 1, y + 1

    op.append("%s %s" % (x + 1, y + 1))

    if x < n - 1 and G[x][y] == G[x + 1][y] == RIGHT:
        G[x][y] = G[x][y + 1] = DOWN
        G[x + 1][y] = 0
    elif y < m - 1 and G[x][y] == G[x][y + 1] == DOWN:
        G[x][y] = G[x + 1][y] = RIGHT
        G[x][y + 1] = 0

def require(G, x, y, d):
    # print "require", x + 1, y + 1

    if G[x][y] != d:
        assert G[x][y]

        if G[x][y] == RIGHT:
            require(G, x + 1, y, RIGHT)
        else:
            require(G, x, y + 1, DOWN)

        rotate(G, x, y)

def process(G):
    global op, D, R

    if n % 2 == 0:
        op = []
        N = deepcopy(G)

        for x in xrange(0, n, 2):
            for y in xrange(m):
                require(N, x, y, DOWN)

        D.append(deepcopy(op))

    if m % 2 == 0:
        op = []
        N = deepcopy(G)

        for x in xrange(n):
            for y in xrange(0, m, 2):
                require(N, x, y, RIGHT)

        R.append(deepcopy(op))

for i in xrange(T + 1):
    G = read_graph()
    process(G)

for i in xrange(T):
    if m % 2 == 1 or n % 2 == 0 and len(D[i]) + len(D[i + 1]) < len(R[i]) + len(R[i + 1]):
        print len(D[i]) + len(D[i + 1])
        if len(D[i]) > 0:
            print "\n".join(D[i])
        print "\n".join(reversed(D[i + 1]))
    else:
        print len(R[i]) + len(R[i + 1])
        if len(R[i]) > 0:
            print "\n".join(R[i])
        print "\n".join(reversed(R[i + 1]))
