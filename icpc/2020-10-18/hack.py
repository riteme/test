from os import *

def sh(x):
	assert not system(x)

sh('g++ F.cpp -fsanitize=undefined -g')
sh('g++ F-std.cpp -O3 -o b.out')

cnt = 0
while True:
	cnt += 1
	print(cnt)
	sh('python3 F-gen.py > F.in')
	sh('./a.out < F.in > F.out')
	sh('./b.out < F.in > F.ans')
	sh('diff -Bb F.out F.ans')
