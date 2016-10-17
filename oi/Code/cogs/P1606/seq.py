import sys
from pprint import pprint

N = int(sys.argv[1])

A = [0, 1]
for i in range(2, N + 1):
    if i % 2 == 0:
        A.append(A[int(i / 2)])
    else:
        A.append(A[int(i / 2)] + A[int((i + 1) / 2)])

def bin(x):
    S = ""
    for i in range(64, -1, -1):
        S += str((x & (1 << i)) >> i)
    return S

last = 0
S = set([1])
for i in range(1, N + 1):
    if A[i] > last:
        last = A[i]

        if not i in S:
            print("Failed.")

        S.add(i * 2 - 1)
        # S.add(i * 2 + 1)
        S.add(i * 4 - 1)
        # S.add(i * 4 + 1)
        print(bin(i), i, A[i], i * 2 - 1, i * 4 - 1)
