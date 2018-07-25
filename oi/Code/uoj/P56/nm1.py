n = int(raw_input())

for i in range(1, n + 1):
    line = raw_input()
    data = line.split()
    for j in range(1, n + 1):
        if data[j - 1] == '1':
            print i, j
