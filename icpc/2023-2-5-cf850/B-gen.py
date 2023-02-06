import sys
import random

n = int(sys.argv[1])
s = ['w'] * n + ['i'] * n + ['n'] * n
random.shuffle(s)

print(1)
print(n)
for i in range(n):
    t = s[3 * i : 3 * i + 3]
    print(''.join(t))
