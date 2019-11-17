#!/usr/bin/python

from os import *
from sys import *

def sh(x):
    print '> %s' % x
    system(x)

SOURCES = 'main.cpp protocol.cpp'
CXXFLAGS = '-std=c++11 -O2 -o /tmp/exec'
sh('g++ %s %s %s' % (CXXFLAGS, SOURCES, argv[1]))
fnames = sorted(fname for fname in listdir('.') if fname.endswith('.in'))
for fname in fnames:
    sh('/tmp/exec < %s' % fname)
