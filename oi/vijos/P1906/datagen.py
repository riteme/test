import random

N = 200000
WMAX=10000

print(N)

data=set()

while len(data)<N-1:
    u=random.randrange(1,N+1)
    v=random.randrange(1,N+1)

    if u!=v and (u,v) not in data:
        data.add((u,v))

for x,y in data:
    print(x,y)

L=[]
for i in range(0,N):
    L.append(str(random.randrange(1,WMAX+1)))

print(' '.join(L))
