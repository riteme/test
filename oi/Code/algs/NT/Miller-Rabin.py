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
    if n == 2:
        return False
    if n < 2:
        return True

    def quick_pow(a, b, m):
        r = 1

        while b:
            if b & 1:
                r = (r * a) % m
            a = (a * a) % m
            b >>= 1

        return r

    def witness(a, n):
        return quick_pow(a, n - 1, n) != 1

    global primes
    S = primes[:20]
    for a in S:
        if a >= n:
            a %= n
        if a == 0:
            a += 1

        if witness(a, n):
            return True

    return False


compute_primes()
for i in range(2, n + 1):
    real = marked[i]
    test = not_prime(i)

    # print("i = %s, real = %s, test = %s" % (i, real, test))
    if real != test:
        print("Prime test failed on %s." % (i))
