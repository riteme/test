import random

n = 22000
q = 100000

print(n, q)
S = 'abcdefghijklmno'
for i in range(n):
    a = ''.join(random.choice(S) for i in range(5))
    print(a + ''.join(list(reversed(a))))
    # print('a' * 10)
for i in range(q):
    print(random.randint(1, n), random.randint(1, n))
