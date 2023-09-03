n = int(input())
p = list(map(int, input().split()))
if n > 1:
    m = max(p[0], max(p[1:]) + 1)
else:
    m = p[0]
print(m - p[0])
