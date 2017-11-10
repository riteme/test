def brute(n):
    cnt = 0
    for a in range(1, n + 1):
        for b in range(a + 1, n + 1):
            for c in range(b + 1, n + 1):
                for d in  range(c + 1, n + 1):
                    if a * d == b * c:
                        print('%s * %s = %s * %s = %s' % (a, d, b, c, a * d))
                        cnt += 1
    return cnt

def c2(n):
    return n * (n - 1) // 2

def cp(l, r, x):
    return r // x - l // x

def calc(n):
    cnt = 0
    sqn = int(sqrt(n))
    print('sqn = ', sqn)
    for a in range(1, sqn + 1):
        for c in range(a + 1, sqn + 1):
            b = lcm(a, c) // a
            cnt += cp(sqn, n, b)
            print(a, c, b, cp(sqn, n, b))
    return cnt
