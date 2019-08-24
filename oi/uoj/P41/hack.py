#!/usr/bin/env pypy

from os import system as sh

sh("g++ main.cpp -g")

cnt = 1
while True:
    sh("./gen.py 100 > data.in")
    sh("./a.out < data.in > data.out")

    mat = []
    with open("data.in", "r") as reader:
        T = reader.readline()
        n, m = map(int, reader.readline().split())
        for i in xrange(n):
            mat.append(map(int, reader.readline().split()))

    with open("data.out", "r") as reader:
        perm = map(int, reader.readline().split())

        for i in xrange(n):
            assert 1 <= perm[i] <= n

            j = 0
            while mat[i][j] != perm[i]:
                j += 1

            while j < m:
                mat[i][j] = perm[i]
                j += 1
        
        for j in xrange(m):
            marked = [False] * n
            for i in xrange(n):
                x = mat[i][j] - 1
                
                if x < 0:
                    continue

                assert not marked[x]
                marked[x] = True
        
        print cnt
        cnt += 1
