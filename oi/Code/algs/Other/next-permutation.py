#!/usr/bin/env python3

def stl_nxt(a):
    i = len(a) - 1
    while i > 0 and a[i] < a[i - 1]:
        i -= 1

    if i == 0:
        return False

    for j in range(len(a) - 1, i - 1, -1):
        if a[j] > a[i - 1]:
            a[i - 1], a[j] = a[j], a[i - 1]
            break
    
    j = len(a) - 1
    while i < j:
        a[i], a[j] = a[j], a[i]
        i += 1
        j -= 1

    return True

def stl_pre(a):
    i = len(a) - 1
    while i > 0 and a[i] > a[i - 1]:
        i -= 1

    if i == 0:
        return False

    for j in range(len(a) - 1, i - 1, -1):
        if a[j] < a[i - 1]:
            a[i - 1], a[j] = a[j], a[i - 1]
            break
    
    j = len(a) - 1
    while i < j:
        a[i], a[j] = a[j], a[i]
        i += 1
        j -= 1

    return True

def print_seq(a):
    print(" ".join([str(x) for x in a]))

n = int(input())
a = list(reversed(range(1, n + 1)))

print_seq(a)
while stl_pre(a):
    print_seq(a)
