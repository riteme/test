import random

number_of_testcases=5
NMAX=200000
VMAX=32767

for i in range(0,number_of_testcases):
    print(NMAX)

    p=0
    for j in range(0,NMAX):
        print('{} {}'.format(random.randrange(0,p+1),random.randrange(0,VMAX+1)))
        p+=1
