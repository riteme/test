import random

C=['0','1']

N=2**10
S=''

for i in range(0,N):
    S+=C[random.randrange(0,2)]

print(10)
print(S)
