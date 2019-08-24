n, k, m = [int(x) for x in raw_input().split()]

data = list(enumerate(
    [int(x) for x in raw_input().split()], start=1
))

data = sorted(data, key=lambda x: x[1])
spec = data[-4:]
data = data[:-4]
data.remove((1, 92752))

print n, m, k

for u, d in spec:
    print data[-1][0], u, d - data[-1][1]

print 1, spec[0][0], 20000
print spec[0][0], spec[1][0], 20000
print spec[1][0], spec[2][0], 20000
print spec[2][0], spec[3][0], 20000
print spec[3][0], 1, 12752

print 1, data[0][0], 20000
print data[0][0], data[0][0], data[0][1] - 20000
print data[0][0], data[1][0], data[1][1] - 20000
print data[1][0], data[1][0], 0

for i in range(2, len(data)):
    print data[i - 1][0], data[i][0], data[i][1] - data[i - 1][1]

for u, d in data[2:]:
    print u, u, 20000
