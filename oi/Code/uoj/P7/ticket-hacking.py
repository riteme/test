#!/usr/bin/env pypy

from os import system as sh

if sh("g++ ticket.cpp -std=c++11 -o ticket.exec"):
    exit(-1)
if sh("g++ ticket-brute.cpp -O3 -o ticket-brute.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./ticket-gen.py 5000 > ticket.in")
    sh("./ticket.exec < ticket.in > ticket.out")
    sh("./ticket-brute.exec < ticket.in > ticket.ans")

    if sh("diff -Bb ticket.out ticket.ans"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
