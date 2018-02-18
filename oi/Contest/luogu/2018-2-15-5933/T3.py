#!/usr/bin/env pypy

FIRST_WIN = 'lsq Win'
LAST_WIN = 'wzt Win'

q = int(raw_input())

while q:
    q -= 1
    a, n = map(int, raw_input().split())

    if a & 1 == 1: # a = 1 included
        if n & 1:
            print FIRST_WIN
        else:
            print LAST_WIN
    else:
        r = n % (a + 1)

        if r >= a - 1:
            print FIRST_WIN
        elif r & 1 == 1:
            print FIRST_WIN
        else:
            print LAST_WIN
