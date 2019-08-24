def gcd(a, b):
  if b == 0:
    return a
  return gcd(b, a % b)

n = int(raw_input())
seq = [int(x) for x in raw_input().split(" ")]
answer = 0
for x in seq:
  answer = gcd(x, answer)

print abs(answer)
