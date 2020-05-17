with open('large.csv', 'r') as fp:
    data = fp.readlines()

for i in range(len(data)):
    data[i] = list(map(float, data[i].split(',')))

n = len(data)
m = len(data[0])
L = []
for i in range(n):
    for j in range(m):
        secs = data[i][j]
        secs %= 12 * 60 * 60
        mins = secs / 60
        hours = mins / 60
        mins = mins % 60
        # print(f'data[{i}][{j}]={hours/12},{mins/60}')
        L.append('s[%.2f,%.2f,%d,%d],' % (hours / 12, mins / 60, j, n - i))
print(f"Show[{''.join(L)[:-1]}]")
