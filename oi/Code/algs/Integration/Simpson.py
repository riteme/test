def sample(f, a, b):
    return ((b - a) / 6) * (f(a) + f((a + b) / 2) * 4 + f(b))

def simpson(f, a, b, n = 100):
    delta = (b - a) / n
    result = 0

    for i in range(0, n):
        left = a + i * delta
        right = left + delta
        result += sample(f, left, right)

    return result

def _adaptive_simpson(f, a, b, eps, current):
    mid = (a + b) * 0.5
    leftans = sample(f, a, mid)
    rightans = sample(f, mid, b)

    if abs(leftans + rightans - current) < eps:
        return current
    else:
        return _adaptive_simpson(f, a, mid, eps * 0.5, leftans) + _adaptive_simpson(f, mid, b, eps * 0.5, rightans)

def adaptive_simpson(f, a, b, eps):
    return _adaptive_simpson(f, a, b, eps, sample(f, a, b))
