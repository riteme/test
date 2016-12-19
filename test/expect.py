import os

def randbits(n = 4):
    return int.from_bytes(os.urandom(n), "big")

def randint(left, right, n = 4):
    return randbits(n) % (right - left + 1) + left

def randfloat(left, right, tail = 4, n = 4):
    return randint(
        left * 10**tail,
        right * 10**tail,
        n) / 10**tail

def randbool():
    return int.from_bytes(os.urandom(1), "big") & 1

def cut_mmid(left, right):
    mid = (left + right) * 0.5
    mmid = (mid + right) * 0.5

    return (mid, mmid)

def cut_three(left, right):
    l = right - left

    return (left + l / 3, left + 2 * l / 3)

def evaluate(left, right, cut, rand, eps = 0.001):
    p = rand(left, right)

    l = left
    r = right
    cnt = 0
    while r - l >= eps:
        lmid, rmid = cut(l, r)

        if p < lmid:
            r = rmid
        elif p > rmid:
            l = lmid
        else:
            flag = randbool()

            if flag:
                l = lmid
            else:
                r = rmid
        
        cnt += 1

    return (cnt, p, l, r)

def sample(n, f, extractor):
    return [extractor(f()) for i in range(0, n)]

def average(S):
    return sum(S) / len(S)

def analyze(n, cut, cases = 10**5, maxv = 10**18):
    print("Analyzing with maxv = %s" % maxv)

    s = 0.0

    for idx in range(1, n + 1):
        data = sample(cases,
                      lambda : evaluate(0, maxv, cut, randfloat),
                      lambda x : x[0])
        a = average(data)
        s += a

        print("Case %s: %s" % (idx, a))

    print("Average: %s" % (s / n, ))

def fac(n):
    if n <= 1:
        return 1
    return fac(n - 1) * n

def c(n, m):
    return fac(n) // fac(m) // fac(n - m)

def dp(W, pl, pr, el, er, eps):
    answer = 0.0
    L = 0
    while True:
        w = W * el**L
        R = 0
        while w >= eps:
            w *= er
            R += 1

        E = (L + R) * c(L + R, R) * pl**L * pr**R
        # print(E, L, R, c(L + R, R))
        answer += E
        
        if R == 0:
            break;

        L += 1
    
    return answer
