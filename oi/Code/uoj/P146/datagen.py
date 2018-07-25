import random

N=200000
L=[]

for i in range(0,N):
    L.append(str(random.randrange(1,N+1)))

print(N)
print(' '.join(L))
