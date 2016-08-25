#!/usr/bin/env pypy

import sys

target = sys.argv[1]

with open(target) as reader:
    reader.readline()

    n = int(reader.readline())

    for i in range(0, 5):
        reader.readline()

    S = set()
    for line in reader:
        x, y = [int(s) for s in line.split(" ")]
        S.add((x, y))

    if len(S) != n:
        print("Incorrect")
    else:
        print("Correct")
