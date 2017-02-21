def gen(n, d):
    for u in range(1, n):
        for v in range(u + 1, n + 1):
            print d + u, d + v

n = 100
m = 950
s = 10

print 1
print n, m, s
gen(20, 0)
gen(20, 20)
gen(20, 40)
gen(20, 60)
gen(20, 80)
