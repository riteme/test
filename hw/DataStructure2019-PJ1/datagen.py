#!/usr/bin/python3

import random
import os
import sys

SEED = 0

data = [[10000, 100], [10000, 100], [10000, 100], [10000, 100], [10000, 100]]

if len(sys.argv) >= 2:
    SEED = int(sys.argv[1])

for num, (n, k) in enumerate(data, start=11):
    filename = 'data/%d.in' % (num + 1)
    command = './maker %d %d %d > %s' % (n, k, random.randint(1, 2**31-1), filename)
    print(command)
    os.system(command)
