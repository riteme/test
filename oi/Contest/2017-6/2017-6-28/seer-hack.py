#!/usr/bin/env pypy

from os import system as sh

sh("g++ seer.cpp -std=c++11 -O3")

def invalid():
    E = []
    with open("seer.in", "r") as reader:
        n, m = map(int, reader.readline().split())

        for i in xrange(m):
            u, v = map(int, reader.readline().split())
            E.append((u - 1, v - 1))

    d = [0] * n
    with open("seer.out", "r") as reader:
        ans = int(reader.readline())
        line = reader.readline().strip()
        for i in xrange(m):
            bit = line[i]

            if bit == '0':
                d[E[i][0]] += 1
                d[E[i][1]] -= 1
            else:
                d[E[i][0]] -= 1
                d[E[i][1]] += 1

    for i in xrange(n):
        if d[i] == 0:
            ans -= 1

    return ans != 0

cnt = 1
while True:
    sh("./seer-gen.py 100 250 > seer.in")
    sh("./a.out < seer.in > seer.out")

    if invalid():
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
