x = []
y = []

def g(i, j):
    if i == j:
        return y[i]
    return (g(i + 1, j) - g(i, j - 1)) / (x[j] - x[i])

def interp(n):
    p = 1
    ret = 0

    for i in range(len(x)):
        ret += g(0, i) * p
        p *= (n - x[i])

    return ret
