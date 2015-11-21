D=int(input('D: '))
I=int(input('I: '))

n=0
for i in range(0,D):
    n+=2**i
# print(n)

T=[]
for i in range(0,n+1):
    T.append(False)

L=[]
for i in range(0,2**(D-1)+1):
    L.append(0)

def left(x):
    return x*2;

def right(x):
    return x*2+1;

for i in range(1,len(L)):
    depth=1
    pos=1
    while depth<D:
        if T[pos]==False:
            pos=left(pos)
        else:
            pos=right(pos)

        T[pos]=not T[pos]
        depth+=1

    L[i]=pos

L[0]=L[len(L)-1]
print(L[I%(len(L)-1)])

# print(' '.join(L))
