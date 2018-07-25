from random import *

C = 16
V = 2 * C + 1
Q = 6

print V
for i in range(0, C):
    u = 2 * i
    print 2, u + 1, 0, u + 2, -1
    print 1, u + 2, -2**(C - i)
print 0

print Q
for i in range(0, Q):
    print 0, V - 1
