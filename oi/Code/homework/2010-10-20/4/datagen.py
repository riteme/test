import random

CHARS=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
N=10
L=[]

for i in xrange(0,N):
    L.append(CHARS[random.randrange(0,len(CHARS))])

print(N)
print(''.join(L))
