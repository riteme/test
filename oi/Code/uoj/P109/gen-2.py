from random import *

V = 96
Q = 10
T = 11

print V
print 0
for u in range(1, V):
    print T, " ".join(["%s %s" % (u - 1, -1)] * T)

print Q
for i in range(0, Q):
    print V - 1, 0
