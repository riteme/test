import random

n=int(input())
s1=''
s2=''

for i in range(0,n):
	s1+=str(random.randrange(0,10))
	s2+=str(random.randrange(0,10))

print(s1)
print(s2)