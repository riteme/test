import random

N=100
L=[]

for i in range(0,N):
    # L.append(str(random.randrange(130,231)))
    L.append(str(i+130))

print(N)
print(' '.join(L))
