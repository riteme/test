#!/usr/bin/env pypy

from sys import argv
from random import *

T, n, m, LIMIT = map(int, argv[1:])

assert n % 2 == 0 or m % 2 == 0, "n and m can't be both odd."

def generate():
    def idx(x, y):
        return x * m + y + 1

    V = idx(n - 1, m - 1) + 1
    G = [0] + [[
        idx(x + dx, y + dy)
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]
        if 0 <= x + dx < n and 0 <= y + dy < m
    ] for x in xrange(n) for y in xrange(m)]
    match = [0] * V

    def dfs(u):
        shuffle(G[u])
        for v in G[u]:
            if marked[v] or match[v] == u:
                continue

            marked[v] = True
            if match[v] and dfs(match[v]) or not match[v]:
                match[u] = v
                match[v] = u
                return True

        return False

    for u in xrange(1, V):
        if not match[u]:
            marked = [False] * V
            dfs(u)

    for x in xrange(n):
        line = []

        for y in xrange(m):
            u = idx(x, y)
            if match[u] == idx(x + 1, y) or match[u] == idx(x - 1, y):
                line.append('$')
            else:
                line.append('#')

        print "".join(line)

print T, n, m, LIMIT
for i in xrange(T + 1):
    generate()
    print ""
