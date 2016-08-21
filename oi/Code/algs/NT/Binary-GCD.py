def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


def bgcd(a, b):
    if b == 0:
        return a
    if a == 0:
        return b
    if a & 1:
        if b & 1:
            return bgcd((a - b) >> 1, b)
        else:
            return bgcd(a, b >> 1)
    else:
        if b & 1:
            return bgcd(a >> 1, b)
        else:
            return bgcd(a >> 1, b >> 1) << 1

n, m = [int(x) for x in raw_input().split(" ")]
result = 0
for i in range(1, n + 1):
    for j in range(1, m + 1):
        result += bgcd(i, j)
