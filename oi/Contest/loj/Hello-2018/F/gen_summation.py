#!/usr/bin/env python

import argparse

parser = argparse.ArgumentParser(description='Compile simplified APP files into Mathematica.')
parser.add_argument('filename', type=str)
filename = parser.parse_args().filename

with open(filename, 'r') as reader:
    L = filter(lambda x : len(x) > 0, [x.strip() for x in reader.read().split('\n')])

class Node(object):
    """Represent a node in a syntax tree"""
    def __init__(self, const):
        super(Node, self).__init__()
        self.const = const
        self.children = []

i = 0
idcnt = 0
lookup = {'n': 'n'}
bounds = []

def parse():
    global i
    global idcnt
    S = []

    assert(L[i][0] == 'f')
    token, a, b, c = L[i].split()
    lookup[a] = 'i' + str(idcnt)
    a = lookup[a]
    idcnt += 1

    if not b.isdigit():
        b = lookup[b]
    if not c.isdigit():
        c = lookup[c]

    bounds.append('{%s,%s,%s}' % (a, b, c))
    i += 1

    while L[i][0] == 'f':
        S.append(parse())

    assert(L[i][0] == 'c')
    token, d = L[i].split()
    i += 1

    if len(S) > 0:
        return 'Sum[Boole[%s<=%s](%s+%s),{%s,%s,%s}]' % (b, a, d, '+'.join(S), a, b, c)
    else:
        return 'Sum[%s*Boole[%s<=%s],{%s,%s,%s}]' % (d, b, a, a, b, c)

print parse()
