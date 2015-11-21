AND='AND'
OR='OR'
XOR='XOR'

def compute(x,op_list):
    result=x;

    for op_name,op_value in op_list:
        if op_name==AND:
            result&=op_value
        elif op_name==OR:
            result|=op_value
        elif op_name==XOR:
            result^=op_value

    return result

op=[]
s=raw_input().split(' ')
n=int(s[0])
m=int(s[1])

for i in range(0,n):
    s=raw_input().split(' ')
    op.append((str(s[0]),int(s[1])))

v=0

for j in range(0,m+1):
    tmp=compute(j,op)

    if v<tmp:
        v=tmp

print(v)
