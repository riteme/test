from random import *

V = 300
Q = 10
T = 48

print V
for i in range(0, V - 2):
    print 1, i, 0
print T, " ".join(["%s 0" % (V - 2)] * T)
print 1, V - 1, -1

print Q
for i in range(0, Q):
    print 0, V - 1
