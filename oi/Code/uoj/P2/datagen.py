import random

NMAX=100000
MMAX=2**30
TMAX=2**30
# OP=['AND','OR','XOR']
OP=['OR']

# N=99715
# M=310984152
N=10000
M=20000
T=TMAX
L=[]

for i in range(0,N):
    L.append(OP[random.randrange(0,len(OP))] + ' ' + str(random.randrange(0,T)))

print(str(N) + ' ' + str(M))
print('\n'.join(L))
