for i in range(20):
    maxv = primes[pos]
    maxp = pos
    for j in range(pos):
        if j > 0 and t[j - 1] == 1:
            break
        if primes[j]**(t[j] + 1) < maxv:
            maxv = primes[j]**(t[j] + 1)
            maxp = j
    t[maxp] += t[maxp] + 1
    if maxp == pos:
        pos += 1
