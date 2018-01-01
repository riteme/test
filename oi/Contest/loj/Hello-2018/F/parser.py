#!/usr/bin/env python

import os
import argparse

parser = argparse.ArgumentParser(description='Compile APP files.')
parser.add_argument('filename', type=str)
filename = parser.parse_args().filename

with open(filename, 'r') as reader:
    L = [x.strip() for x in reader.read().split('\n')]
    L = filter(lambda x : len(x) > 0, L)

idcnt = 0
cur = 0
stk = [0] * 512
lookup = {'n': 'n'}
for i in xrange(len(L)):
    if L[i].startswith('Func'):
        cur += 1
        L[i] = L[i].replace('Func', '#define')
        L[i] += '(n) for i%s 1 1 $ \\' % idcnt
        idcnt += 1
    elif L[i] == 'S':
        stk[cur] += 1
    elif L[i].startswith('F '):
        _, a, b, c = L[i].split()

        lookup[a] = 'i' + str(idcnt)
        a = lookup[a]
        idcnt += 1

        if not b.isdigit():
            b = lookup[b]
        if not c.isdigit():
            c = lookup[c]

        L[i] = 'for %s %s %s $ \\' % (a, b, c)
        cur += 1
    elif L[i] == 'E':
        L[i] = 'case %s' % stk[cur]
        if cur > 1:
            L[i] += ' $ \\'

        stk[cur] = 0
        cur -= 1
    else:  # Function call
        target, var = L[i].split()
        if not var.isdigit():
            var = lookup[var]

        L[i] = '%s(%s) $ \\' % (target, var)

pre, ext = filename.split('.')
newfile = '%s.cpp' % pre
with open(newfile, 'w') as writer:
    L.append('Main(n)')
    writer.write('\n'.join(filter(lambda x : x != 'S', L)))

os.system('g++ %s -E > tmp' % newfile)
os.system('mv tmp %s' % newfile)

with open(newfile, 'r') as reader:
    content = reader.read()

content = content.split('\n')[-2]
content = content.replace('$ ', '\n')
content = content.replace('%', ' ')
with open(newfile, 'w') as writer:
    L = content.split('\n')
    cur = 0
    for x in L:
        if x[0] == 'f':
            writer.write(' ' * cur + x + '\n')
            cur += 1
        else:
            cur -= 1
            writer.write(' ' * cur + x + '\n')
