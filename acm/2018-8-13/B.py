P = []
f = []
def primes():
    P = []
    mark = [0]*1000001
    for i in xrange(2, 1000001):
        if mark[i]:
            continue
        P.append(i)
        for j in xrange(i + i, 1000001, i):
            mark[j] = 1
    return P

def calc():
    for p in P:
        for i in xrange(p + p, 1000001, p):
            f[i] = f[i / p] * f[p]
    pre = 0
    for i in xrange(1, 1000001):
        pre += f[i]
        if abs(pre) > 20:
            print pre, i
            return (pre, i)
    print 'OK'
    return True

def search(x, d):
    for p in reversed(P):
        if f[p] == d and p <= x:
            print p
            return p

def fuck():
    dat = calc()
    if dat == True:
        print 'OK'
        return False
    else:
        print dat
        d = 0
        if dat[0] > 0:
            d = -1
        else:
            d = 1
        p = search(dat[1], -d)
        f[p] = d
        print 'f[' + str(p) + '] = ' + str(d)
        return True
