#!/usr/bin/env pypy

from sys import stdin
from copy import copy, deepcopy
from collections import deque
from time import sleep

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

def rotate(G, x, y):
    if x < n - 1 and G[x][y] == G[x + 1][y] == RIGHT:
        G[x][y] = G[x][y + 1] = DOWN
        G[x + 1][y] = 0
    elif y < m - 1 and G[x][y] == G[x][y + 1] == DOWN:
        G[x][y] = G[x + 1][y] = RIGHT
        G[x][y + 1] = 0
    else:
        return False

    return True

def encode(G):
    s = 0
    for x in xrange(n):
        for y in xrange(m):
            if G[x][y] == DOWN:
                s |= 1 << (x * m + y)

    return s

def decode(s):
    G = [[0] * m for i in xrange(n)]
    for x in xrange(n):
        for y in xrange(m):
            p = x * m + y

            if s & (1 << p):
                G[x][y] = DOWN
            elif ((y == 0 or G[x][y - 1] != RIGHT) and
                  (x == 0 or G[x - 1][y] != DOWN)):
                G[x][y] = RIGHT

    return G

def bfs(S, T):
    s = encode(S)
    t = encode(T)
    q = [deque([s]), deque([t])]
    r = [{s : None}, {t : None}]

    def finish(u):
        op = []
        x = u
        while x != s:
            p = r[0][x]
            op.append(p[1:])
            x = p[0]

        op.reverse()
        x = u
        while x != t:
            p = r[1][x]
            op.append(p[1:])
            x = p[0]

        print len(op)
        for x, y in op:
            print x + 1, y + 1

    def expand(i):
        u = q[i].popleft()

        G = decode(u)
        for x in xrange(n):
            for y in xrange(m):
                M = deepcopy(G)
                if rotate(M, x, y):
                    v = encode(M)

                    if v in r[i]:
                        continue

                    r[i][v] = (u, x, y)
                    q[i].append(v)

                    if v in r[i ^ 1]:
                        finish(v)
                        return True

    while True:
        # sleep(0.01)
        # print len(r[0]), len(r[1])
        if len(r[0]) <= len(r[1]):
            if expand(0):
                break
        else:
            if expand(1):
                break

S = read_graph()
for i in xrange(T):
    T = read_graph()
    bfs(S, T)
    S = T
