from random import *

n = 0
n = int(raw_input())

primes = []
marked = [False] * (n + 1)


def compute_primes():
    global primes
    global marked

    marked[0] = True
    marked[1] = True
    for i in range(2, n + 1):
        if not marked[i]:
            primes.append(i)

        for p in primes:
            if i * p > n:
                break

            marked[i * p] = True

            if i % p == 0:
                break


def not_prime(n):
    BASIS = [2, 7, 61]

    if n in BASIS:
        return False

    def quick_pow(a, b, p):
        r = 1

        while b:
            if b & 1:
                r = r * a % p
            a = a * a % p
            b >>= 1

        return r

    # 将n - 1分解为2^r * t的形式，t是奇数
    r = 0
    t = n - 1
    while not(t & 1):
        t >>= 1
        r += 1

    for b in BASIS:
        v = quick_pow(b % n, t, n)

        for i in range(0, r):
            u = v * v % n
            if u == 1 and v != 1 and v != n - 1:
                return True
            v = u

        if v != 1:
            return True

    return False


compute_primes()
for i in range(2, n + 1):
    real = marked[i]
    test = not_prime(i)

    # print("i = %s, real = %s, test = %s" % (i, real, test))
    if real != test:
        print("Prime test failed on %s." % (i))
