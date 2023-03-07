import random

n = 100000

print(n)
a = list(range(1, n + 1))
for _ in range(2):
    random.shuffle(a)
    for i in range(0, n - 1):
        print(a[i], a[i + 1], random.randint(1, 10**9))
