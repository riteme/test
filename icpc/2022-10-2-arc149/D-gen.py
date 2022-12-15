import random

n = 3 * 10**5
m = n
print(n, m)
print(' '.join(str(random.randint(1, 10**6)) for i in range(n)))
print(' '.join(str(random.randint(1, 5)) for i in range(m)))
