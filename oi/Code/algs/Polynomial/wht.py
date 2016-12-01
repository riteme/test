import numpy
import copy

def fwt(X):
    if len(X) == 1:
        return X
    m = len(X) // 2
    L = fwt(X[:m])
    R = fwt(X[m:])
    return numpy.array([*(L + R), *(L - R)])

def rfwt(X):
    if len(X) == 1:
        return X
    m = len(X) // 2
    L = rfwt(X[:m])
    R = rfwt(X[m:])
    return numpy.array([*((L + R) * 0.5), *((L - R) * 0.5)])

def iterative_fwt(X):
    A = copy.deepcopy(X)
    s = 2
    while s <= len(X):
        for i in range(0, len(X), s):
            for j in range(0, s // 2):
                tmp = A[i + j]
                A[i + j] += A[i + j + s // 2]
                A[i + j + s // 2] = tmp - A[i + j + s // 2]
        s *= 2

    return A

def iterative_rfwt(X):
    A = copy.deepcopy(X)
    s = 2
    while s <= len(X):
        for i in range(0, len(X), s):
            for j in range(0, s // 2):
                tmp = A[i + j]
                A[i + j] = (A[i + j] + A[i + j + s // 2]) / 2
                A[i + j + s // 2] = (tmp - A[i + j + s // 2]) / 2
        s *= 2

    return A
