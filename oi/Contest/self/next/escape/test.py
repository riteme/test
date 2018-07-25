import numpy as np
import itertools

def sgn(P):
    answer = 0

    for i in range(0, len(P)):
        for j in range(i + 1, len(P)):
            if P[i] > P[j]:
                answer += 1

    if answer % 2 == 0:
        return 1
    else:
        return -1

def det1(M):
    w, h = M.shape
    assert w == h, "Width must equal to height"

    value = 0
    for P in itertools.permutations(range(w), w):
        prod = 1

        for i, j in enumerate(P):
            prod *= M[i][j]

        value += sgn(P) * prod

    return value
