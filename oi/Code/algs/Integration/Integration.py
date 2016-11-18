def linear(f, a, b):
    return (b - a) * (f(a) + f(b)) * 0.5

def quadratic(f, a, b):
    return (b - a) * (f(a) + f((a + b) / 2) * 4 + f(b)) / 6

def cubic(f, a, b):
    return (b - a) * (f(a) + 3 * f((2 * a + b) / 3) + 3 * f((a + 2 * b) / 3) + f(b)) * 0.125

sampler = quadratic

def integration(f, a, b, n = 100):
    delta = (b - a) / n
    result = 0

    for i in range(0, n):
        left = a + i * delta
        right = left + delta
        result += sampler(f, left, right)

    return result

def _adaptive_cubic(f, a, b, eps, current):
    lmid = (2 * a + b) / 3
    rmid = (a + 2 * b) / 3
    ans1 = cubic(f, a, lmid)
    ans2 = cubic(f, lmid, rmid)
    ans3 = cubic(f, rmid, b)

    if abs(ans1 + ans2 + ans3 - current) < eps:
        return current
    else:
        return (_adaptive_cubic(f, a, lmid, eps / 3, ans1) +
                _adaptive_cubic(f, lmid, rmid, eps / 3, ans2) +
                _adaptive_cubic(f, rmid, b, eps / 3, ans3)
               )

def adaptive_cubic(f, a, b, eps):
    return _adaptive_cubic(f, a, b, eps, cubic(f, a, b))

def _adaptive_integration(f, a, b, eps, current):
    mid = (a + b) * 0.5
    leftans = sampler(f, a, mid)
    rightans = sampler(f, mid, b)

    if abs(leftans + rightans - current) < eps:
        return current
    else:
        return (_adaptive_integration(f, a, mid, eps * 0.5, leftans) +
               _adaptive_integration(f, mid, b, eps * 0.5, rightans))

def adaptive_integration(f, a, b, eps):
    return _adaptive_integration(f, a, b, eps, sampler(f, a, b))
