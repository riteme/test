#!/usr/bin/env pypy

out = open("B.out", "r")
ans = open("B.ans", "r")

score = 0
for i in xrange(1000):
    a = out.readline()
    b = ans.readline()

    if a.strip() == b.strip():
        score += 2
    else:
        score -= 1

out.close()
ans.close()

print score
