#!/usr/bin/env python

M = [
    [1, -1],
    [1, 0]
]

def product(A, B):
    return [
        [A[0][0] * B[0][0] + A[0][1] * B[1][0],
         A[0][0] * B[0][1] + A[0][1] * B[1][1]],
        [A[1][0] * B[0][0] + A[1][1] * B[1][0],
         A[1][0] * B[0][1] + A[1][1] * B[1][1]]
    ]

R = [
    [1, 0],
    [0, 1]
]

n = int(raw_input())

if n <= 1:
    print 1
    exit(0)

n -= 1

while n:
    if n & 1:
        R = product(R, M)
    M = product(M, M)
    n >>= 1

print R[0][0] + R[0][1] * 2
