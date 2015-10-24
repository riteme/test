import random

N=100
LENGTH=1000

data='1234567890'
L=[]
for i in range(0,N):
    s=[]
    for j in range(0,LENGTH):
        s.append(data[random.randrange(0,10)])

    L.append(''.join(s))

print(N)
print(' '.join(L))
