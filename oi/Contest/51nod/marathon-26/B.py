n, m = map(int, raw_input().split())

if n < 1000 and m >= (1 << n):
    print 0
else:
    ans = 1
    while m:
        if m & 1:
            ans <<= 1
        m >>= 1
    print ans
