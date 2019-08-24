#!/usr/bin/env python3

from os import system as sh
from random import *

cnt = 1
NMAX = 10**18
while True:
    sh("echo %s > data.in" % randint(1, NMAX))
    sh("./pollard_rho.py < data.in > data.out")
    sh("factor < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
