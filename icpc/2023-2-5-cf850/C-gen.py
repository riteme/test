import sys
import random

n = int(sys.argv[1])

print(3)
for i in range(3):
    print(n)
    print(' '.join(str(random.randint(1, n)) for i in range(n)))
