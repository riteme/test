#!/usr/bin/env pypy

from os import system as sh

sh('g++ grader.cpp rts.cpp -g')

cnt = 0
while True:
    cnt += 1
    print cnt

    sh('./gen.py 7 > data.in')
    sh('./a.out < data.in > data.out')

    with open('data.out', 'r') as reader:
        l = reader.readline()
        if l.strip() != 'Correct':
            print 'Hacked!'
            break;