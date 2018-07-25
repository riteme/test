import random

N=50000
L=[]

for i in range(0,N):
    L.append(str(random.randrange((-10)**9,10**9+1)))

print(N)
print(' '.join(L))
