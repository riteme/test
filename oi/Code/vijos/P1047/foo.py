def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

a, b=[int(x) for x in raw_input().split(" ")]
print(a * b / gcd(a, b))
