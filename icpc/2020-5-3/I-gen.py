from random import *

L = 10**9
n = 3000
A = set()
while len(A) < n:
    A.add(randint(1, L))
B = set()
while len(B) < n:
    B.add(randint(1, L))

print(L, n)
A = list(A)
B = list(B)
shuffle(A)
shuffle(B)
print(' '.join(map(str, A)))
print(' '.join(map(str, B)))