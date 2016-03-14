#
# Copyright 2016 riteme
#

fact_map = {}

def fact(n):
    global fact_map

    if n == 0:
        return 1
    else:
        if n in fact_map:
            return fact_map[n]

        result = 1

        for i in range(2, n + 1):
            result *= i

        fact_map[n] = result
        return result

def p(n, r):
    return fact(n) / fact(n - r)

def c(n, r):
    return p(n, r) / fact(r)
