n, k, m = [int(x) for x in raw_input().split()]

print n, m, k
for i in range(1, n + 1):
    data = raw_input().split()

    for j in range(1, n + 1):
        if data[j - 1] == '1':
            print i, j, 0
