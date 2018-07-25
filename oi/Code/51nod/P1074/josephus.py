n, q = map(int, raw_input().split())
N = n * q
while N > n:
    N = (N - n - 1) / (q - 1) + N - n
print N
