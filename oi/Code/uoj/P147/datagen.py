#!/usr/bin/env python3

import sys

from random import *

if len(sys.argv) < 2:
    print("Usage: %s [N]" % sys.argv[0])
    exit(-1)

n = int(sys.argv[1])
cnt = [0] * 15
put = 0;

while put < n:
    v = randrange(0, 15)
    put += 1

    if 0 <= v < 13 and cnt[v] < 3:
        cnt[v] += 1
    elif 13 <= v and cnt[v] == 0:
        cnt[v] = 1
    else:
        put -= 1

print("1 %s\n" % n)
for i in range(0, 15):
    for j in range(0, cnt[i]):
        if 0 <= i < 13:
            print("%s 0" % (i + 1))
        elif i == 13:
            print("0 1")
        else:
            print("0 2")

print("")
