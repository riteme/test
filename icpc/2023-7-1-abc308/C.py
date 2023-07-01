from fractions import Fraction as Q

n = int(input())
a = []
for i in range(n):
  A, B = list(map(int, input().split()))
  a.append((-Q(A, A + B), i + 1))
print(' '.join(str(i) for _, i in sorted(a)))
