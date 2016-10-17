#!/usr/bin/env pypy

from os import system as sh
from random import *

sh("g++ network.cpp -g -std=c++11 -o a.out")
sh("g++ brute.cpp -O2 -o brute")

def random_string(n):
    return "".join([chr(randint(ord('a'), ord('z'))) for i in range(0, n)])

while True:
    sh("./datagen.py 1000 2000 1000000000 > network.in")
    sh("./a.out")
    sh("./brute")

    if sh("diff -b -B network.out brute.out"):
        print("Hacked!")
        exit(0)
    else:
        print(random_string(7))
